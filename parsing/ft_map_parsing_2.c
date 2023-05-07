/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parsing_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:18:22 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/07 18:16:58 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_map_size(t_list *tmp, t_vec2 *map_size)
{
	map_size->y = lst_size(tmp);
	map_size->x = get_longest_line(tmp);
	if (map_size->x < 3 || map_size->y < 3)
		return (false);
	return (true);
}

bool	parse_map_into_charmap(t_list *submap, t_config *config)
{
	t_vec2	map_size;
	t_list	*tmp;
	t_list	*tmp2;
	int		i;

	tmp = submap->next;
	if (parse_map_size(tmp, &map_size) == false)
		return (false);
	tmp = get_equal_lines(tmp, map_size.x);
	if (!tmp)
		return (false);
	config->map = (char **)ft_calloc(sizeof(char *), (map_size.y + 1));
	if (!config->map)
		return (lst_clear(&tmp, free), false);
	tmp2 = tmp;
	lst_iter(tmp, map_str_transform);
	i = 0;
	while (i < map_size.y && tmp)
	{
		config->map[i] = ft_strdup((char *)tmp->content);
		i++;
		tmp = tmp->next;
	}
	config->map_size = map_size;
	return (lst_clear(&tmp2, free), true);
}

bool	parse_map(t_list *head, t_config *config)
{
	t_list	*submap;

	submap = NULL;
	submap = parse_submap(head, 0, "MUSCLE");
	if (parse_map_illegal_instruction(submap) == false)
		return (lst_clear(&submap, free), \
				ft_error("Error\nIllegal instruction in map\n"));
	if (parse_map_illegal_character(submap) == false)
		return (lst_clear(&submap, free), \
				ft_error("Error\nIllegal character in map\n"));
	if (parse_map_closed(submap) == false)
		return (lst_clear(&submap, free), \
				ft_error("Error\nMap not closed\n"));
	if (parse_map_players(submap, config) == false)
		return (lst_clear(&submap, free), \
				ft_error("Error\nInvalid player\n"));
	if (parse_map_into_charmap(submap, config) == false)
		return (lst_clear(&submap, free), \
				ft_error("Error\nMalloc error"));
	return (lst_clear(&submap, free), true);
}

void	free_map(t_config *config)
{
	int	i;

	xfree(&config->north_texture);
	xfree(&config->south_texture);
	xfree(&config->west_texture);
	xfree(&config->east_texture);
	i = 0;
	if (config->map != NULL)
	{
		while (config->map[i] != NULL)
		{
			xfree(&config->map[i]);
			i++;
		}
	}
	xfree(&config->map);
}
