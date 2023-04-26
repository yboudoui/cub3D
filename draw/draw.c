/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:21:13 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/26 18:07:13 by yboudoui         ###   ########.fr       */
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

t_pixel	pixel_create(int x, int y, int raw_color)
{
	return ((t_pixel){
		.coord = (t_vec2){x, y},
		.color.raw = raw_color
	});
}

void	draw_floor_and_ceiling(t_screen *s, t_color ground, t_color ceiling)
{
	t_quad	g;
	t_quad	c;

	g.point[0][0] = pixel_create(0, s->size.y / 2, ground.raw);
	g.point[0][1] = pixel_create(s->size.x, s->size.y / 2, ground.raw);
	g.point[1][0] = pixel_create(0, s->size.y, ground.raw);
	g.point[1][1] = pixel_create(s->size.x, s->size.y, ground.raw);

	c.point[0][0] = pixel_create(0, 0, ceiling.raw);
	c.point[0][1] = pixel_create(s->size.x, 0, ceiling.raw);
	c.point[1][0] = pixel_create(0, s->size.y / 2, ceiling.raw);
	c.point[1][1] = pixel_create(s->size.x, s->size.y / 2, ceiling.raw);
	image_put_quad(s->img, c);
	image_put_quad(s->img, g);
}

#define DIST 800

float	deg_to_rad(float deg)
{
	return (deg * M_PI / 180);
}

void	draw_image(t_screen *screen)
{
	t_data	*data;
	float	distance;
	float	wall_height;
	int		index;
	float	angle;

	data = screen->data;
	index = 0;
	draw_floor_and_ceiling(screen, (t_color){.raw = 0xFF00FF}, (t_color){.raw = 0x0000FF});
	float	pad = 60.0 / screen->size.x;
	while (index < screen->size.x)
	{
		angle = (data->player.view - 30) + (pad * index);
		distance = dda_checker(data->player.pos, angle, data->map);
		distance *= cosf(deg_to_rad(-30 + (index * pad))); //fish_eye correcteur
		wall_height = 1 / distance * DIST;
		image_put_line(screen->img,
			(t_pixel){.coord = (t_vec2){index, screen->center.y + (wall_height / 2)}, .color.raw = 0xFFFF00},
			(t_pixel){.coord = (t_vec2){index, screen->center.y - (wall_height / 2)}, .color.raw = 0x00FFFF});
		index += 1;
	}
}
