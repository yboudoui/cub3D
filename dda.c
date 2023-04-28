/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:26:37 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/28 13:26:22 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_dda {
	t_vec2f	point;
	t_vec2f	pad;
}	t_dda;

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

/*
	new_h = vec2f_add(pos, horizontal.pad);
	new_v = vec2f_add(pos, vertical.pad);
*/
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
