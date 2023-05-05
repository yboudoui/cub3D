/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:21:13 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/05 18:58:06 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_image	*image_env(t_screen *s, t_color ground, t_color ceiling)
{
	t_quad	g;
	t_quad	c;
	t_image	*out;

	out = image_new(s->mlx, s->size);
	c = rectangle(
			(t_vec2){0, (s->size.y / 2) - 1},
			(t_vec2){s->size.x, (s->size.y / 2) - 1},
			ceiling);
	g = rectangle(vec2(0), (t_vec2){s->size.x, s->size.y / 2}, ground);
	image_put_quad(out, c);
	image_put_quad(out, g);
	return (out);
}

#define DIST 800

void	update_wall_distance(t_screen *screen)
{
	t_data			*data;
	int				index;
	float			angle;

	data = screen->data;
	index = -1;
	while (++index < screen->size.x)
	{
		angle = (data->player.view - 30) + (data->pre.pad * index);
		angle = wrap_angle(angle);
		int t = angle / 360.0 * data->pre.size;
		data->walls[index] = dda(data->player.pos, t, data->map);
	}
}

int	find_column_in_texture(t_image *img, t_dda dda)
{
	float	pos;

	if (dda.boundarie == EAST || dda.boundarie == WEST)
		pos = dda.point.y - floor(dda.point.y);
	if (dda.boundarie == NORTH || dda.boundarie == SOUHT)
		pos = dda.point.x - floor(dda.point.x);
	return (img->size.x * pos);
}

void	image_put_image_line(t_image *dest, t_image *src, t_line line, t_dda dda, t_normal_map nmap, t_data *data, int angle)
{
	int		index;
	int		size;
	float	scale;
	int		col;
	t_pixel	pix;

	float	similarity;
	t_vec2f	a;
	t_vec2f	b;

	col = find_column_in_texture(src, dda);
	index = -1;
	size = abs(line.start.coord.y - line.end.coord.y);
	scale = (float)((float)src->size.y / (float)size);
	while (++index < size)
	{
		pix = image_get_pixel(src, (t_vec2){col, index * scale});
		a.x = nmap.map[pix.coord.y][pix.coord.x].y;
		a.y = nmap.map[pix.coord.y][pix.coord.x].z;
		if (dda.boundarie == NORTH)
			a.y *= -1;
		if (dda.boundarie == EAST)
			a.x *= -1;
		b.x = data->pre.cos[angle];
		b.y = data->pre.sin[angle];
		similarity = 1 - cosin_similarity(a, b);
		color_contrast(&pix.color, -similarity);
//		color_brightness(&pix.color, -similarity);
		image_put_pixel(dest, (t_pixel){
			.coord = (t_vec2){.x = line.start.coord.x, .y = line.start.coord.y + index},
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
	t_line	line;

	data = screen->data;
	index = -1;
	image_put_to_image(data->floor_ceilling, screen->img);
	update_wall_distance(screen);
	while (++index < screen->size.x)
	{
		wall = data->walls[index].len;
		wall *= cosf(deg_to_rad(-30 + (index * pad))); //fish_eye correcteur
		wall = 1 / wall * DIST;
		line = (t_line){
			.start.coord = (t_vec2){index, screen->center.y - (wall / 2)},
			.end.coord = (t_vec2){index, screen->center.y + (wall / 2)},
		};
		texture = data->texture[data->walls[index].boundarie];
		image_put_image_line(screen->img, texture, line, data->walls[index], data->nmap, data, (int)(data->player.view / 360.0 * data->pre.size));
	}
//	draw_minimap(screen);
}
