/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:26:37 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/03 11:18:48 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	dda_cross_debug(t_screen *screen, t_vec2f cross, t_color color, int size)
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

static t_dda	dda_horizontal(t_vec2f pos, float angle, t_map map, t_screen *screen)
{
	t_dda	out;
	t_vec2f	pad;
	t_vec2	p;

	out = (t_dda){.angle = angle, .len = INFINITY };
	if (angle == 0 || angle == 180)
		return (out);
	if (angle > 0 && angle < 180)
	{
		out.point.y = floor(pos.y) - pos.y;
		out.boundarie = SOUHT;
		pad.y = -1;
	}
	else
	{
		out.point.y = 1 - (pos.y - floor(pos.y));
		out.boundarie = NORTH;
		pad.y = 1;
	}
	pad.x = pad.y / tanf(deg_to_rad(angle));
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
		out.len = vec2f_dist(out.point, pos);
		dda_cross_debug(screen, out.point, (t_color){.raw = 0xFF0000}, 3);
		if (map.data[p.y - (angle > 0 && angle < 180)][p.x] == '1')
			return(out);
		out.point = vec2f_add(out.point, pad);
		p = (t_vec2){
			.x = (int)out.point.x,
			.y = (int)out.point.y,
		};
	}
	return ((t_dda){ .len = INFINITY });
}

static t_dda	dda_vertical(t_vec2f pos, float angle, t_map map, t_screen *screen)
{
	t_dda	out;
	t_vec2f	pad;
	t_vec2	p;

	out = (t_dda){ .angle = angle, .len = INFINITY };
	if (270 == angle || angle == 90)
		return (out);
	if (angle > 90 && angle < 270)
	{
		out.point.x = 1 - (pos.x - floor(pos.x));
		out.boundarie = EAST;
		pad.x = +1;
	}
	else
	{
		out.point.x = floor(pos.x) - pos.x;
		out.boundarie = WEST;
		pad.x = -1;
	}
	out.point.y = out.point.x * tanf(deg_to_rad(angle));
	pad.y = pad.x * tanf(deg_to_rad(angle));

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
		out.len = vec2f_dist(out.point, pos);
		if (map.data[p.y][p.x - !(angle > 90 && angle < 270)] == '1')
			return(out);
		out.point = vec2f_add(out.point, pad);
		p = (t_vec2){
			.x = (int)out.point.x,
			.y = (int)out.point.y,
		};
	}
	return ((t_dda){ .len = INFINITY });
}

t_dda	dda_checker(t_vec2f pos, float angle, t_map map, t_screen *screen)
{
	t_dda	dist_h;
	t_dda	dist_v;
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
	if (dist_h.len < dist_v.len)
		return (dist_h);
	return (dist_v);
}
