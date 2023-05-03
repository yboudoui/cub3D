/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:14:30 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/03 12:06:48 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "screen.h"
# include "image.h"
# include <math.h>

typedef enum e_boundarie {
	NORTH,
	SOUHT,
	EAST,
	WEST,
	MAX_BOUNDARIE,
}	t_boundarie;

typedef struct s_dda {
	t_vec2f		point;
	float		angle;
	float		len;
	t_boundarie	boundarie;
}	t_dda;

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

typedef struct s_precompute {
	float	pad;
	float	*tan_arr;
}	t_precompute;

typedef struct s_data {
	t_map		map;
	t_image		*mini_map;
	t_image		*dda_debugger;
	t_player	player;
	t_dda		*walls;
	t_image		*texture[MAX_BOUNDARIE];
	t_precompute	pre;
}	t_data;

void	draw_image(t_screen *data);
bool	update_state(t_screen *data);

float	deg_to_rad(float deg);
float	wrap_angle(float angle_deg);

t_dda	dda_checker(t_vec2f pos, float angle, t_map map, t_screen *screen);

t_precompute	precompute_tan(float fov, int screen_width);
#include <stdio.h>
#endif
