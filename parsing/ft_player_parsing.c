/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:50:38 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/04 15:50:50 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool check_number_of_players(t_list *submap)
{
	t_list *tmp;
	char *str;
	int i;
	int count;

	tmp = submap;
	count = 0;
	while (tmp)
	{
		i = 0;
		str = (char *)tmp->content;
		while (str[i])
		{
			if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
				count++;
			i++;
		}
		tmp = tmp->next;
	}
	if (count != 1)
		return (false);
	return (true);
}

void get_player_angle(float *player_angle, char c)
{
	if (c == 'N')
		*player_angle = 90;
	else if (c == 'S')
		*player_angle = 270;
	else if (c == 'W')
		*player_angle = 0;
	else if (c == 'E')
		*player_angle = 180;
}

bool get_player_position(t_list *submap, t_config *config)
{
	t_list *tmp;
	char *str;
	int i;
	int j;

	tmp = submap->next;
	i = 0;
	while (tmp)
	{
		j = 0;
		str = (char *)tmp->content;
		while (str[j])
		{
			if (str[j] == 'N' || str[j] == 'S' || str[j] == 'W' || str[j] == 'E')
			{
				config->player_pos.x = j;
				config->player_pos.y = i;
				get_player_angle(&config->player_angle, str[j]);
				return (true);
			}
			j++;
		}
		i++;
		tmp = tmp->next;
	}
	return (false);
}

bool parse_map_players(t_list *submap, t_config *config)
{
	if (check_number_of_players(submap) == false)
		return (false);
	if (get_player_position(submap, config) == false)
		return (false);
	return (true);
}
