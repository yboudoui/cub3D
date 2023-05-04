/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:00:54 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/04 16:01:03 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_config(t_config *config)
{
	config->north_texture = NULL;
	config->south_texture = NULL;
	config->west_texture = NULL;
	config->east_texture = NULL;
	config->set_floor_color = false;
	config->set_ceiling_color = false;
	config->floor_color = (t_color){{1, 1, 1}};
	config->ceiling_color = (t_color){{1, 1, 1}};
	config->map = NULL;
	config->player_pos.x = -1;
	config->player_pos.y = -1;
	config->player_angle = -1;
	return ;
}

bool ends_with(char *str, char *end)
{
	int	str_len;
	int	end_len;

	str_len = ft_strlen(str);
	end_len = ft_strlen(end);
	if (str_len < end_len)
		return (false);
	if (ft_strncmp(str + str_len - end_len, end, end_len) == 0)
		return (true);
	return (false);
}

int open_file(char *filename)
{
	int	fd;

	if ((open(filename, O_DIRECTORY)) != -1)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

bool check_syntax(char c)
{
	if (ft_isalnum(c) || ft_is_nl_comma_fslash_dot(c) || ft_isspace(c))
		return (true);
	return (false);
}

bool wrong_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!check_syntax(str[i]))
			return (false);
		i++;
	}
	return (true);
}
