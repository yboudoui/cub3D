/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:21:13 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/02 17:23:15 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_floor_and_ceiling(t_screen *s, t_color ground, t_color ceiling)
{
	t_quad	g;
	t_quad	c;

	g = rectangle(vec2(0,0), vec2(s->size.x, s->size.y / 2), ground);
	c = rectangle(vec2(0,s->size.y / 2), vec2(s->size.x, s->size.y / 2), ceiling);
	image_put_quad(s->img, c);
	image_put_quad(s->img, g);
}

#define DIST 800

float	deg_to_rad(float deg)
{
	return (deg * M_PI / 180);
}

void	draw_minimap_grid(t_screen *screen)
{
	t_data	*data;
	t_quad	block;
	const t_vec2	block_size = {16, 16};
	t_vec2	pos;

	data = screen->data;
	pos = (t_vec2){0, 0};
	while (pos.y < data->map.size.y)
	{
		pos.x = 0;
		while (pos.x < data->map.size.x)
		{
			block = rectangle(mul_vec2(pos, block_size), block_size, (t_color){.raw = 0xDDDDDD});
			image_put_empty_quad(data->mini_map, block);
			pos.x += 1;
		}
		pos.y += 1;
	}
//	image_put_to_image(data->mini_map, screen->img);
}


void	draw_minimap(t_screen *screen)
{
	t_data	*data;
	t_quad	block;
	const t_vec2	block_size = {16, 16};
	t_vec2	pos;

	data = screen->data;
	image_clear(data->mini_map, (t_color){.raw = 0xFFFFFF});
	draw_minimap_grid(screen);
	pos = (t_vec2){0, 0};
	while (pos.y < data->map.size.y)
	{
		pos.x = 0;
		while (pos.x < data->map.size.x)
		{
			if (data->map.data[pos.y][pos.x] == '1')
			{
				block = rectangle(mul_vec2(pos, block_size), block_size, (t_color){.raw = 0x0});
				image_put_empty_quad(data->mini_map, block);
			}
			pos.x += 1;
		}
		pos.y += 1;
	}
}

void	update_minimap(t_screen *screen)
{
	int	index;
	t_data	*data;
	t_pixel	new;
	t_pixel	pos;

	draw_minimap(screen);
	data = screen->data;
	index = 0;
	pos.color.raw = 0xFF0000;
	pos.coord.x = (data->player.pos.x * 16);
	pos.coord.y = (data->player.pos.y * 16);
	while (index < screen->size.x)
	{
		new = pos;
		new.coord.x -= cos(deg_to_rad(data->walls[index].angle)) * (data->walls[index].distance * 16);
		new.coord.y -= sin(deg_to_rad(data->walls[index].angle)) * (data->walls[index].distance * 16);
		image_put_line(data->mini_map, pos, new);
		index += 1;
	}
}

void	update_wall_distance(t_screen *screen)
{
	t_data	*data;
	int		index;
	float	angle;
	float	pad = 60.0 / screen->size.x;

	data = screen->data;
//	screen->size.x = 1;
	index = 0;
	while (index < screen->size.x)
	{
		angle = (data->player.view - 30) + (pad * index);
		angle = wrap_angle(angle);
//		angle = (data->player.view) + (pad * index);
		data->walls[index].distance = dda_checker(data->player.pos, angle, data->map, screen);
		data->walls[index].angle = angle;
		index += 1;
	}
}

void	draw_image(t_screen *screen)
{
	t_data	*data;
	float	wall;
	int		index;
	float	pad = 60.0 / screen->size.x;

	data = screen->data;
	index = 0;
	draw_floor_and_ceiling(screen, (t_color){.raw = 0xFF00FF}, (t_color){.raw = 0x0000FF});
	update_wall_distance(screen);
	while (index < screen->size.x)
	{
		wall = data->walls[index].distance;
		wall *= cosf(deg_to_rad(-30 + (index * pad))); //fish_eye correcteur
		wall = 1 / wall * DIST;
		image_put_line(screen->img,
			(t_pixel){.coord = (t_vec2){index, screen->center.y + (wall / 2)}, .color.raw = 0xFFFF00},
			(t_pixel){.coord = (t_vec2){index, screen->center.y - (wall / 2)}, .color.raw = 0x00FFFF});
		index += 1;
	}
	update_minimap(screen);


	image_put_to_image(data->dda_debugger, data->mini_map);
	image_put_to_image(data->mini_map, screen->img);
	image_put_to_image(data->dda_debugger, screen->img);
//	mlx_string_put(screen->mlx->mlx, screen->mlx->win, 200, 200, 0, "hello world");
}
