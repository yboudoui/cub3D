/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors_parsing_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:22:48 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/05 18:23:12 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_ceiling_color(t_list *head, t_config *config)
{
	t_list	*tmp;
	char	*str;
	char	*color_path;

	tmp = head;
	while (tmp)
	{
		str = (char *)tmp->content;
		if (check_texture_name(str, "C ") == true)
		{
			color_path = get_color_path(str, "C");
			if (color_path == NULL)
				return (false);
			if (config->set_ceiling_color)
				return (false);
			if (parse_color_path(color_path, \
						&config->ceiling_color, \
						&config->set_ceiling_color) == false)
				return (false);
		}
		tmp = tmp->next;
	}
	if (config->set_ceiling_color)
		return (true);
	return (false);
}

bool	parse_colors(t_list *head, t_config *config)
{
	if (parse_floor_color(head, config) == false)
		return (false);
	if (parse_ceiling_color(head, config) == false)
		return (false);
	return (true);
}
