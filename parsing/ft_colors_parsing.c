/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:09:56 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/04 18:41:17 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *get_color_path(char *line, char *color_name)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			i++;
			continue;
		}
		if (ft_strncmp(line + i, color_name, 1) == 0)
		{
			i++;
			while (line[i] && ft_isspace(line[i]))
				i++;
			return (ft_strdup(line + i));
		}
		i++;
	}
	return (NULL);
}

bool parse_color_path(char *color_path, t_color *trgb_color, bool *set_color)
{
	int	i;
	int	j;
	int	color[3];

	i = 0;
	j = 0;
	while (color_path[i])
	{
		if (ft_isdigit(color_path[i]))
		{
			color[j] = ft_atoi(color_path + i);
			j++;
			while (ft_isdigit(color_path[i]))
				i++;
			if (color_path[i] == ',')
				i++;
			else if (color_path[i] == '\n')
				i++;
			else if (ft_isspace(color_path[i]))
				i++;
			else if (color_path[i] != '\0')
				return (false);
		}
		else if (ft_isspace(color_path[i]))
			i++;
		else if (color_path[i] == ',')
			i++;
		else
			return (false);
	}	
	if (j != 3)
		return (false);
	if (color[0] < 0 || color[0] > 255)
		return (false);
	if (color[1] < 0 || color[1] > 255)
		return (false);
	if (color[2] < 0 || color[2] > 255)
		return (false);
	*trgb_color = create_trgb(0, color[0], color[1], color[2]);
	*set_color = true;
	return (true);
}

bool parse_floor_color(t_list *head, t_config *config)
{
	t_list *tmp;
	char *str;
	char *color_path;

	tmp = head;
	while (tmp)
	{
		str = (char *)tmp->content;
		if (check_texture_name(str, "F ") == true)
		{
			color_path = get_color_path(str, "F");
			if (color_path == NULL)
				return (false);
			if (config->set_floor_color)
				return (false);
			if (parse_color_path(color_path, \
						&config->floor_color, \
						&config->set_floor_color) == false)
				return (false);
		}
		tmp = tmp->next;
	}
	if (config->set_floor_color)
		return (true);
	return (false);
}

bool parse_ceiling_color(t_list *head, t_config *config)
{
	t_list *tmp;
	char *str;
	char *color_path;

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

bool parse_colors(t_list *head, t_config *config)
{
	if (parse_floor_color(head, config) == false)
		return (false);
	if (parse_ceiling_color(head, config) == false)
		return (false);
	return (true);
}
