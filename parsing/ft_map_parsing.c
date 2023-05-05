/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:53:28 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/05 18:57:03 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_map_illegal_instruction(t_list *map)
{
	t_list	*tmp;
	char	*str;

	tmp = map;
	while (tmp)
	{
		str = (char *)tmp->content;
		if (check_texture_name(str, "NO") == true)
			return (false);
		if (check_texture_name(str, "SO") == true)
			return (false);
		if (check_texture_name(str, "WE") == true)
			return (false);
		if (check_texture_name(str, "EA") == true)
			return (false);
		if (check_texture_name(str, "F") == true)
			return (false);
		if (check_texture_name(str, "C") == true)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

bool	parse_legal_map_characters(char c)
{
	if (c == ' ' || c == '1' || \
			c == '0' || c == 'N' || c == 'S' || \
			c == 'W' || c == 'E' || c == '\n')
		return (true);
	return (false);
}

bool	parse_map_illegal_character(t_list *map)
{
	t_list	*tmp;
	char	*str;
	int		i;

	tmp = map;
	while (tmp)
	{
		i = 0;
		str = (char *)tmp->content;
		while (str[i])
		{
			if (parse_legal_map_characters(str[i]) == false)
				return (false);
			i++;
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	zero_or_player_condition(char *str, char *str_prev, int i)
{
	if (i == 0 || i == ft_strlen(str) - 1)
		return (false);
	if (str[i - 1] == ' ' || str[i + 1] == ' '\
			|| str[i - 1] == '\n' || str[i + 1] == '\n')
		return (false);
	if (str_prev[i] == ' ' || str_prev[i + 1] == ' '\
			|| str_prev[i] == '\n' || str_prev[i + 1] == '\n')
		return (false);
	return (true);
}

bool	parse_map_closed(t_list *submap)
{
	t_list			*tmp;
	//t_list			*tmp_prev;
	char			*str;
	char			*str_prev;
	unsigned long	i;

	tmp = submap->next;
	str_prev = (char *)submap->content;
	while (tmp)
	{
		i = -1;
		str = (char *)tmp->content;
		while (str[++i])
		{
			if (zero_or_player(str[i]))
			{
				if (tmp->next == NULL /*|| tmp_prev == NULL \*/
						|| !zero_or_player_condition(str, str_prev, i))
					return (false);
			}
		}
		str_prev = str;
		//tmp_prev = tmp;
		tmp = tmp->next;
	}
	return (true);
}
#include <stdio.h>

bool parse_map_into_charmap(t_list *submap, t_config *config)
{
	t_vec2 map_size;
	t_list *tmp;
	int	i;

	tmp = submap->next;
	map_size.y = lst_size(tmp);
	map_size.x = get_longest_line(tmp);
	printf("map_size.x = %d\n", map_size.x);
	printf("map_size.y = %d\n", map_size.y);
	if (map_size.x < 3 || map_size.y < 3)
		return (false);
	tmp = get_equal_lines(tmp, map_size.x);
	if (!tmp)
		return (false);
	config->map = (char **)ft_calloc(sizeof(char *), (map_size.y + 1));
	if (!config->map)
		return (false);
	lst_iter(tmp, map_str_transform);
	i = 0;
	while (i < map_size.y && tmp)
	{
		config->map[i] = (char *)tmp->content;
		i++;
		tmp = tmp->next;
	}
	return (true);
}

bool parse_map(t_list *head, t_config *config)
{
	t_list *submap;

	submap = NULL;
	submap = parse_submap(head);
	if (parse_map_illegal_instruction(submap) == false)
		return (ft_error("Error\nIllegal instruction in map"));
	if (parse_map_illegal_character(submap) == false)
		return (ft_error("Error\nIllegal character in map"));
	if (parse_map_closed(submap) == false)
		return (ft_error("Error\nMap not closed"));
	if (parse_map_players(submap, config) == false)
		return (ft_error("Error\nInvalid player"));
	if (parse_map_into_charmap(submap, config) == false)
		return (ft_error("Error\nMalloc error"));
	debug(config);
	exit(0);
}
