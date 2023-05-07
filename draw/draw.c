/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:21:13 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/07 16:35:33 by yboudoui         ###   ########.fr       */
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
	t_data	*data;
	int		index;
	int		angle;

	data = screen->data;
	angle = data->player.view - data->player.hfov;
	index = -1;
	while (++index < screen->size.x)
		data->walls[index] = dda(data->player.pos, angle + index, data->map);
}

void	normal(t_normal_map nmap, t_pixel *pix, t_dda dda, int angle)
{
	t_vec2f	a;
	t_vec2f	b;
	float	similarity;

	a.x = nmap.map[pix->coord.y][pix->coord.x].y;
	a.y = nmap.map[pix->coord.y][pix->coord.x].z;
	if (dda.boundarie == NORTH)
		a.y *= -1;
	if (dda.boundarie == EAST)
		a.x *= -1;
	b.x = precompute(NULL).angle[angle].cos;
	b.y = precompute(NULL).angle[angle].sin;
	similarity = 1 - cosin_similarity(a, b);
	color_contrast(&pix->color, -similarity);
}

void	image_put_image_line(t_image *dest, int height, t_data *data, int i)
{
	int		index;
	float	scale;
	int		col;
	t_pixel	pix;
	t_dda	dda;

	dda = data->walls[i];
	if (dda.boundarie == EAST || dda.boundarie == WEST)
		scale = dda.point.y - floor(dda.point.y);
	if (dda.boundarie == NORTH || dda.boundarie == SOUHT)
		scale = dda.point.x - floor(dda.point.x);
	col = data->texture[dda.boundarie]->size.x * scale;
	scale = ((float)data->texture[dda.boundarie]->size.y / (float)height);
	index = -1;
	while (++index < height)
	{
		pix.coord = (t_vec2){col, (int)(index * scale)};
		pix.color = data->texture[dda.boundarie]->column[col][pix.coord.y];
		pix.coord = (t_vec2){i, dest->center.y - (height / 2) + index};
		image_put_pixel(dest, pix);
	}
}

void	draw_image(t_screen *screen)
{
	t_data	*data;
	float	wall;
	int		index;

	data = screen->data;
	index = -1;
	image_put_to_image(data->floor_ceilling, screen->img);
	update_wall_distance(screen);
	while (++index < screen->size.x)
	{
		wall = data->walls[index].len;
		wall *= precompute(0).angle[
			y_wrap_angle(index - data->player.hfov)].cos;
		wall = 1 / wall * DIST;
		image_put_image_line(screen->img, wall, data, index);
	}
}
