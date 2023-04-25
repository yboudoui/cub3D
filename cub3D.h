/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:14:30 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/25 18:43:42 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "screen.h"
# include "image.h"
# include <math.h>

typedef struct s_data {
	char	**map;
	int		cube_size;
	t_vec2f	player_pos;
	float	player_view;
}	t_data;

#include <stdio.h>

void	draw_image(t_screen *data);
bool	update_state(t_screen *data);

float	dda_checker(t_vec2f player_pos, float angle_view, char **map, int cube_size);
#endif
