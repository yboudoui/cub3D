/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:14:30 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/05 18:47:18 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "screen.h"
# include "texture.h"
# include <math.h>

typedef enum e_boundarie {
	NORTH,
	SOUHT,
	EAST,
	WEST,
	MAX_BOUNDARIE,
}	t_boundarie;

typedef struct s_map {
	char	**data;
	t_vec2	size;
}	t_map;

typedef struct s_dda {
	t_vec2f		point;
	int			angle;
	float		len;
	t_boundarie	boundarie;
}	t_dda;

t_dda			dda(t_vec2f pos, int angle, t_map map);

typedef struct s_player {
	t_vec2f	pos;
	float	view;
	float	fov;
	float	mouse_speed;
}	t_player;

typedef struct s_precompute {
	float	pad;
	int		size;
	int		limit[MAX_BOUNDARIE];
	float	*tan;
	float	*cos;
	float	*sin;
}	t_precompute;

t_precompute	precompute(t_precompute *in);
t_precompute	precompute_tan(float fov, int screen_width);

typedef struct s_data {
	t_map			map;
	t_image			*mini_map;
	t_image			*dda_debugger;
	t_player		player;
	t_dda			*walls;
	t_image			*floor_ceilling;
	t_image			*texture[MAX_BOUNDARIE];
	t_normal_map	nmap;
	t_precompute	pre;
}	t_data;

t_image			*image_env(t_screen *s, t_color ground, t_color ceiling);
void			init_minimap(t_screen *screen);

void			draw_image(t_screen *data);
bool			update_state(t_screen *data);

float			deg_to_rad(float deg);
float			wrap_angle(float angle_deg);


void			draw_minimap(t_screen *screen);

#endif
