/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parsing_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:18:22 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/06 18:27:10 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_map_into_charmap(t_list *submap, t_config *config)
{
	t_vec2	map_size;
	t_list	*tmp;
	int		i;

	tmp = submap->next;
	map_size.y = lst_size(tmp);
	map_size.x = get_longest_line(tmp);
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

bool	parse_map(t_list *head, t_config *config)
{
	t_list	*submap;

	submap = NULL;
	submap = parse_submap(head, 0, "MUSCLE");
	if (parse_map_illegal_instruction(submap) == false)
		return (ft_error("Error\nIllegal instruction in map\n"));
	if (parse_map_illegal_character(submap) == false)
		return (ft_error("Error\nIllegal character in map\n"));
	if (parse_map_closed(submap) == false)
		return (ft_error("Error\nMap not closed\n"));
	if (parse_map_players(submap, config) == false)
		return (ft_error("Error\nInvalid player\n"));
	if (parse_map_into_charmap(submap, config) == false)
		return (ft_error("Error\nMalloc error"));
	debug(config);
	exit(0);
}
