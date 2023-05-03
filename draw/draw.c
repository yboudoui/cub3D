/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:21:13 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/03 12:08:35 by yboudoui         ###   ########.fr       */
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
		new.coord.x -= cos(deg_to_rad(data->walls[index].angle)) * (data->walls[index].len * 16);
		new.coord.y -= sin(deg_to_rad(data->walls[index].angle)) * (data->walls[index].len * 16);
		image_put_line(data->mini_map, pos, new);
		index += 1;
	}
}

void	update_wall_distance(t_screen *screen)
{
	t_data	*data;
	int		index;
	float	angle;

	data = screen->data;
	index = -1;
	while (++index < screen->size.x)
	{
		angle = (data->player.view - 30) + (data->pre.pad * index);
		angle = wrap_angle(angle);
		data->walls[index] = dda_checker(data->player.pos, angle, data->map, screen);
	}
}

int		find_column_in_texture(t_image *img, t_dda dda)
{
	float	pos;

	if (dda.boundarie == EAST || dda.boundarie == WEST)
		pos = dda.point.y - floor(dda.point.y);
	if (dda.boundarie == NORTH || dda.boundarie == SOUHT)
		pos = dda.point.x - floor(dda.point.x);
	return (img->size.x * pos);
}

void	image_put_image_line(t_image *dest, t_image *src, t_vec2 start, t_vec2 end, int col)
{
	int		index;
	int		size;
	float	scale;
	t_pixel	pix;

	index = -1;
	size = abs(start.y - end.y);
	scale = (float)((float)src->size.y / (float)size);
	while (++index < size)
	{
		pix = image_get_pixel(src, (t_vec2){col, index * scale});
		image_put_pixel(dest, (t_pixel){
			.coord = (t_vec2){.x = start.x, .y = start.y + index},
			.color = pix.color,
		});
	}
}

void	draw_image(t_screen *screen)
{
	t_data	*data;
	float	wall;
	int		index;
	float	pad = 60.0 / screen->size.x;
	t_image	*texture;
	int		col;

	data = screen->data;
	index = -1;
	draw_floor_and_ceiling(screen, (t_color){.raw = 0xFF00FF}, (t_color){.raw = 0x0000FF});
	update_wall_distance(screen);
	while (++index < screen->size.x)
	{
		wall = data->walls[index].len;
		wall *= cosf(deg_to_rad(-30 + (index * pad))); //fish_eye correcteur
		wall = 1 / wall * DIST;
		texture = data->texture[data->walls[index].boundarie];
		col = find_column_in_texture(texture, data->walls[index]);
		image_put_image_line(screen->img, texture,
			(t_vec2){index, screen->center.y - (wall / 2)},
			(t_vec2){index, screen->center.y + (wall / 2)},
			col
		);
	}

	update_minimap(screen);

	image_put_to_image(data->dda_debugger, data->mini_map);
	image_put_to_image(data->mini_map, screen->img);
	image_put_to_image(data->dda_debugger, screen->img);
}
