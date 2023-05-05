/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:58:29 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/05 15:19:34 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_texture_north(t_list *head, t_config *config)
{
	t_list	*tmp;
	char	*str;

	tmp = head;
	while (tmp)
	{
		str = (char *)tmp->content;
		if (check_texture_name(str, "NO ") == true)
		{
			if (config->north_texture)
				return (false);
			config->north_texture = get_texture_path(str, "NO");
		}
		tmp = tmp->next;
	}
	if (config->north_texture)
		return (true);
	return (false);
}

bool	parse_texture_south(t_list *head, t_config *config)
{
	t_list	*tmp;
	char	*str;

	tmp = head;
	while (tmp)
	{
		str = (char *)tmp->content;
		if (check_texture_name(str, "SO ") == true)
		{
			if (config->south_texture)
				return (false);
			config->south_texture = get_texture_path(str, "SO");
		}
		tmp = tmp->next;
	}
	if (config->south_texture)
		return (true);
	return (false);
}

bool	parse_texture_west(t_list *head, t_config *config)
{
	t_list	*tmp;
	char	*str;

	tmp = head;
	while (tmp)
	{
		str = (char *)tmp->content;
		if (check_texture_name(str, "WE ") == true)
		{
			if (config->west_texture)
				return (false);
			config->west_texture = get_texture_path(str, "WE");
		}
		tmp = tmp->next;
	}
	if (config->west_texture)
		return (true);
	return (false);
}

bool	parse_texture_east(t_list *head, t_config *config)
{
	t_list	*tmp;
	char	*str;

	tmp = head;
	while (tmp)
	{
		str = (char *)tmp->content;
		if (check_texture_name(str, "EA ") == true)
		{
			if (config->east_texture)
				return (false);
			config->east_texture = get_texture_path(str, "EA");
		}
		tmp = tmp->next;
	}
	if (config->east_texture)
		return (true);
	return (false);
}

bool	valid_texture_name(char *str)
{
	if (check_texture_name(str, "NO ") == true)
		return (true);
	else if (check_texture_name(str, "SO ") == true)
		return (true);
	else if (check_texture_name(str, "WE ") == true)
		return (true);
	else if (check_texture_name(str, "EA ") == true)
		return (true);
	else if (check_texture_name(str, "C ") == true)
		return (true);
	else if (check_texture_name(str, "F ") == true)
		return (true);
	else
		return (false);
}
