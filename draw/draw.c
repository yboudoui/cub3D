/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:21:13 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/25 18:46:33 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/*
static inline void	drawer(t_screen *screen, t_quad quad)
{
	int	mode;

	mode = 1;
	if (mode == 1)
		image_put_quad(screen->img, quad);
	else
		image_put_empty_quad(screen->img, quad);
}
*/
#define DIST 250

void	draw_image(t_screen *screen)
{
	t_data	*data;
	float	distance;
	float	wall_height;
	int		index;
	float	angle;

	data = screen->data;
	angle = data->player_view - 30;
	index = 0;
	image_clear(screen->img, (t_color){.raw = 0x0});
	while (index < screen->size.x)
	{
		angle = (data->player_view - 30) + ((60.0 / screen->size.x) * index);
		distance = dda_checker(data->player_pos, angle, data->map, data->cube_size);
		if (index < (screen->size.x /2))
			distance *=  cosf(-angle * M_PI / 180.0);
		else
			distance *=  cosf(angle * M_PI / 180.0);
		wall_height = data->cube_size / distance * DIST;
		image_put_line(screen->img,
			(t_pixel){.coord = (t_vec2){index, screen->center.y + (wall_height / 2)}, .color.raw = 0xFFFF00},
			(t_pixel){.coord = (t_vec2){index, screen->center.y - (wall_height / 2)}, .color.raw = 0x00FFFF});
		index += 1;
	}
}

/*
void	draw_image(t_screen *screen)
{
	t_quad	quad;
	t_color	a;
	t_color	b;
	t_data	*data;

	data = screen->data;

	quad = (t_quad){0};
	a = create_trgb(1, 255, 0, 0);
	b = create_trgb(1, 0, 0, 255);

	quad.point[0][0] = (t_pixel){
		.coord = (t_vec2){screen->center.x, 50},
		.color.raw = 0xFFFFFF
	};
	quad.point[0][1] = (t_pixel){
		.coord = (t_vec2){screen->center.x, 590},
		.color.raw = 0xFFFFFF
	};
	quad.point[1][0] = (t_pixel){
		.coord = (t_vec2){410, 50},
		.color.raw = 0xFFFFFF
	};
	quad.point[1][1] = (t_pixel){
		.coord = (t_vec2){410, 590},
		.color.raw = 0xFFFFFF
	};

	float distance;
	float wall_height;

	distance = dda_checker(data->player_pos, data->player_view, data->map, data->cube_size);
	wall_height = data->cube_size / distance * DIST;

//	printf("%f %f\n", distance, wall_height);
	quad.point[0][0].coord.y = screen->center.y + (wall_height / 2);
	quad.point[1][0].coord.y = screen->center.y + (wall_height / 2);

	printf("%f\n", wall_height);
	distance = dda_checker(data->player_pos, data->player_view + 30, data->map, data->cube_size);
	wall_height = data->cube_size / distance * DIST;
	quad.point[0][1].coord.y = screen->center.y - (wall_height / 2);
	quad.point[1][1].coord.y = screen->center.y - (wall_height / 2);

	printf("%f\n", wall_height);
//	printf("%f\n",data->player_view);
//	printf("%d %d\n", quad.point[0][0].coord.y, quad.point[0][1].coord.y);
	const t_color	g_BLACK = (t_color){.raw = 0};
	image_clear(screen->img, g_BLACK);
	drawer(screen, quad);
}
*/
