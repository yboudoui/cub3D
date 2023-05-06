/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:53:28 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/06 18:20:56 by kdhrif           ###   ########.fr       */
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
	int	str_prev_len;
	int	str_len;

	str_prev_len = ft_strlen(str_prev);
	str_len = ft_strlen(str);
	if (i < 0 || i >= str_len || i >= str_prev_len)
		return (false);
	if (i == 0 || i == (int)ft_strlen(str) - 1)
		return (false);
	if (ft_isspace(str[i - 1]) || ft_isspace(str[i + 1]))
		return (false);
	if (ft_isspace(str_prev[i]) || str_prev[i] == '\0')
		return (false);
	return (true);
}

bool	parse_map_closed(t_list *submap)
{
	t_list			*tmp;
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
				if (tmp->next == NULL
					|| !zero_or_player_condition(str, str_prev, i))
					return (false);
			}
		}
		str_prev = str;
		tmp = tmp->next;
	}
	return (true);
}
