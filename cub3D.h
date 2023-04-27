/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:14:30 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/27 17:26:19 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "screen.h"
# include "image.h"
# include <math.h>

typedef struct s_map {
	char	**data;
	t_vec2	size;
}	t_map;

typedef struct s_player {
	t_vec2f	pos;
	float	view;
	float	fov;
	float	mouse_speed;
}	t_player;

typedef struct s_wall {
	float	distance;
	float	angle;
}	t_wall;

typedef struct s_data {
	t_map		map;
	t_image		*mini_map;
	t_player	player;
	t_wall		*walls;
}	t_data;

void	draw_image(t_screen *data);
bool	update_state(t_screen *data);

float	dda_checker(t_vec2f pos, float angle, t_map map);
#include <stdio.h>
#endif
