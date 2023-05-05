/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:09:56 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/05 18:25:55 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_color_path(char *line, char *color_name)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			i++;
			continue ;
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

bool	check_color_values(int *color, int count)
{
	if (count != 3)
		return (false);
	if (color[0] < 0 || color[0] > 255)
		return (false);
	if (color[1] < 0 || color[1] > 255)
		return (false);
	if (color[2] < 0 || color[2] > 255)
		return (false);
	return (true);
}

bool	get_colors_from_path(char *color_path, int *color, int *count, int i)
{
	while (color_path[i] && *count < 3)
	{
		while (ft_isspace(color_path[i]))
			i++;
		if (ft_isdigit(color_path[i]))
		{
			color[*count] = ft_atoi(color_path + i);
			(*count)++;
		}
		else
			return (false);
		while (ft_isdigit(color_path[i]))
			i++;
		while (ft_isspace(color_path[i]))
			i++;
		if (color_path[i] == ',')
			i++;
		else if (color_path[i] == '\n')
			break ;
		else if (color_path[i] != '\0')
			return (false);
	}
	return (true);
}

bool	parse_color_path(char *color_path, t_color *trgb_color, bool *set_color)
{
	int	i;
	int	count;
	int	color[3];

	i = 0;
	count = 0;
	while (color_path[i])
	{
		if (ft_isdigit(color_path[i]))
		{
			if (get_colors_from_path(color_path, color, &count, i) == false)
				return (false);
			else
				break ;
		}
		else if (ft_isspace(color_path[i]))
			i++;
		else if (color_path[i] == ',')
			return (false);
		return (false);
	}	
	if (check_color_values(color, count) == false)
		return (false);
	*trgb_color = create_trgb(0, color[0], color[1], color[2]);
	return (*set_color = true, true);
}

bool	parse_floor_color(t_list *head, t_config *config)
{
	t_list	*tmp;
	char	*str;
	char	*color_path;

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
