/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:26:37 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/02 17:32:04 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_dda {
	t_vec2f	point;
	t_vec2f	pad;
}	t_dda;
/*
static t_dda	dda_horizontal(t_vec2f pos, float angle)
{
	t_dda	out;

	if (180 > angle && angle > 0)
	{
		out.point.y = round(pos.y) - 1;
		out.pad.y = -1;
	}
	else
	{
		out.point.y = round(pos.y) + 1;
		out.pad.y = 1;
	}
	angle =  (angle * M_PI / 180.0);
	out.point.x = pos.x + (pos.y - out.point.y) / tanf(angle);
	out.pad.x = 1 / tanf(angle);
	return (out);
}

static t_dda	dda_vertical(t_vec2f pos, float angle)
{
	t_dda	out;

	if (270 < angle && angle > 90)
	{
		out.point.x = round(pos.x) - 1;
		out.pad.x = 1;
	}
	else
	{
		out.point.x = round(pos.x) + 1;
		out.pad.x = -1;
	}
	angle =  (angle * M_PI / 180.0);
	out.point.y = pos.y + (pos.x - out.point.x) * tanf(angle);
	out.pad.y = 1 * tanf(angle);
	return (out);
}

static bool	map_hit(t_map map, t_vec2 point)
{
	map.size = add_vec2(map.size, vec2(-1, -1));
	return (0
			|| !vec2i_in_range(point, vec2(0,0), map.size)
			|| map.data[point.y][point.x] == '1');
}


float	dda_checker(t_vec2f pos, float angle, t_map map)
{
	t_dda	horizontal;
	t_dda	vertical;

	t_vec2f	new_h;
	t_vec2f	new_v;

	float	dist_h;
	float	dist_v;

	float	total_len;

	total_len = 0;

	horizontal = dda_horizontal(pos, angle);
	vertical = dda_vertical(pos, angle);


//	new_h = vec2f_add(pos, horizontal.pad);
//	new_v = vec2f_add(pos, vertical.pad);

	new_h = horizontal.point;
	new_v = vertical.point;

	while (!map_hit(map, vec2f_floor(pos)))
	{
		dist_h = vec2f_dist(pos, new_h);
		dist_v = vec2f_dist(pos, new_v);
		if (dist_h < dist_v)
		{
			pos = new_h;
			new_h = vec2f_add(pos, horizontal.pad);
			total_len += dist_h;
		}
		else
		{
			pos = new_v;
			new_v = vec2f_add(pos, vertical.pad);
			total_len += dist_v;
		}
	}
	return (total_len);
}
*/

static void		dda_cross_debug(t_screen *screen, t_vec2f cross, t_color color, int size)
{
	t_quad	block;
	t_vec2	pos;
	t_data	*data;

	data = screen->data;
	pos = (t_vec2){
		.x = (int)(cross.x * 16) - 1,
		.y = (int)(cross.y * 16) - 1,
	};
	block = rectangle(pos, (t_vec2){size, size}, color);
	image_put_empty_quad(data->dda_debugger, block);
}

static float	dda_horizontal(t_vec2f pos, float angle, t_map map, t_screen *screen)
{
	t_dda	out;
	float	len;
	t_vec2	p;

	if (angle == 0 || angle == 180)
		return (INFINITY);
	if (angle > 0 && angle < 180)
	{
		out.point.y = floor(pos.y) - pos.y;
		out.pad.y = -1;
	}
	else
	{
		out.point.y = 1 - (pos.y - floor(pos.y));
		out.pad.y = 1;
	}
	out.pad.x = out.pad.y / tanf(deg_to_rad(angle));
	out.point.x = out.point.y / tanf(deg_to_rad(angle));

	out.point.x += pos.x;
	out.point.y += pos.y;
	dda_cross_debug(screen, out.point, (t_color){.raw = 0x0}, 5);
	p = (t_vec2){
		.x = (int)(out.point.x),
		.y = (int)(out.point.y),
	};
	while (vec2i_in_range(p, vec2(0,0), map.size))
	{
		len = vec2f_dist(out.point, pos);
		dda_cross_debug(screen, out.point, (t_color){.raw = 0xFF0000}, 3);
		if (map.data[p.y - (angle > 0 && angle < 180)][p.x] == '1')
			return(len);
		out.point = vec2f_add(out.point, out.pad);
		p = (t_vec2){
			.x = (int)out.point.x,
			.y = (int)out.point.y,
		};
	}
	return (INFINITY);
}

static float	dda_vertical(t_vec2f pos, float angle, t_map map, t_screen *screen)
{
	t_dda	out;
	float	len;
	t_vec2	p;

	if (270 == angle || angle == 90)
		return (INFINITY);
	if (angle > 90 && angle < 270)
	{
		out.point.x = 1 - (pos.x - floor(pos.x));
		out.pad.x = +1;
	}
	else
	{
		out.point.x = floor(pos.x) - pos.x;
		out.pad.x = -1;
	}
	out.point.y = out.point.x * tanf(deg_to_rad(angle));
	out.pad.y = out.pad.x * tanf(deg_to_rad(angle));

	out.point.x += pos.x;
	out.point.y += pos.y;
	p = (t_vec2){
		.x = (int)out.point.x,
		.y = (int)out.point.y,
	};
	dda_cross_debug(screen, out.point, (t_color){.raw = 0x0}, 5);
	while (vec2i_in_range(p, vec2(0,0), map.size))
	{
		dda_cross_debug(screen, out.point, (t_color){.raw = 0x00FF00}, 3);
		len = vec2f_dist(out.point, pos);
		if (map.data[p.y][p.x - !(angle > 90 && angle < 270)] == '1')
			return(len);
		out.point = vec2f_add(out.point, out.pad);
		p = (t_vec2){
			.x = (int)out.point.x,
			.y = (int)out.point.y,
		};
	}
	return (INFINITY);
}

float	dda_checker(t_vec2f pos, float angle, t_map map, t_screen *screen)
{
	float	dist_h;
	float	dist_v;
	t_data	*data;

	data = screen->data;
/*
	static float a = 0;

	if (data->player.view != a)
	{
		printf("%f\n", data->player.view);
		a = data->player.view;
	}
*/
	map.size = add_vec2(map.size, vec2(-1, -1));
	image_clear(data->dda_debugger, (t_color){.raw = 0xFFFFFFFF});
	dist_h = dda_horizontal(pos, angle, map, screen);
	dist_v = dda_vertical(pos, angle, map, screen);
	/* printf("%f %f\n", dist_h, dist_v); */
	if (dist_h < dist_v)
		return (dist_h);
	return (dist_v);
}
