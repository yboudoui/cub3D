/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:26:37 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/07 16:24:24 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_dda	dda_len(t_dda dda, t_map map, t_vec2f pos, t_vec2f pad)
{
	t_vec2	p;

	dda.point = vec2f_add(dda.point, pos);
	p = vec2f_floor(dda.point);
	while (vec2i_in_range(p, vec2(0), map.size))
	{
		dda.len = vec2f_dist(dda.point, pos);
		if (map.data
			[p.y - (dda.boundarie == SOUHT)]
			[p.x - (dda.boundarie == WEST)] == '1')
			return (dda);
		dda.point = vec2f_add(dda.point, pad);
		p = vec2f_floor(dda.point);
	}
	return ((t_dda){.len = INFINITY});
}

static t_dda	dda_horizontal(t_vec2f pos, int angle, t_map map)
{
	t_dda			out;
	t_vec2f			pad;
	t_precompute	pre;

	out = (t_dda){0};
	pre = precompute(NULL);
	if (angle == pre.limit[NORTH] || angle == pre.limit[SOUHT])
		return ((t_dda){.len = INFINITY});
	if (angle > pre.limit[NORTH] && angle < pre.limit[SOUHT])
	{
		out.point.y = floor(pos.y) - pos.y;
		out.boundarie = SOUHT;
		pad.y = -1;
	}
	else
	{
		out.point.y = 1 - (pos.y - floor(pos.y));
		out.boundarie = NORTH;
		pad.y = +1;
	}
	pad.x = pad.y / pre.angle[angle].tan;
	out.point.x = out.point.y / pre.angle[angle].tan;
	return (dda_len(out, map, pos, pad));
}

static t_dda	dda_vertical(t_vec2f pos, int angle, t_map map)
{
	t_dda			out;
	t_vec2f			pad;
	t_precompute	pre;

	out = (t_dda){0};
	pre = precompute(NULL);
	if (angle == pre.limit[EAST] || angle == pre.limit[WEST])
		return ((t_dda){.len = INFINITY});
	if (angle > pre.limit[EAST] && angle < pre.limit[WEST])
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
	out.point.y = out.point.x * pre.angle[angle].tan;
	pad.y = pad.x * pre.angle[angle].tan;
	return (dda_len(out, map, pos, pad));
}

t_dda	dda(t_vec2f pos, int angle, t_map map)
{
	t_dda	dist_h;
	t_dda	dist_v;

	angle = y_wrap_angle(angle);
	map.size = vec2_add(map.size, vec2(-1));
	dist_h = dda_horizontal(pos, angle, map);
	dist_v = dda_vertical(pos, angle, map);
	if (dist_h.len < dist_v.len)
		return (dist_h);
	return (dist_v);
}
