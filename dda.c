/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:26:37 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/27 17:25:58 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vec2f	add_vec2f(t_vec2f a, t_vec2f b)
{
	t_vec2f	out;

	out.x = a.x + b.x;
	out.y = a.y + b.y;
	return (out);
}

float	vec2f_dist(t_vec2f a, t_vec2f b)
{
	t_vec2f	dist;

	dist.x = fabsf(a.x - b.x);
	dist.y = fabsf(a.y - b.y);
	return (sqrtf(powf(dist.x, 2) + powf(dist.y, 2)));
}

typedef struct s_dda {
	t_vec2f	point;
	t_vec2f	pad;
}	t_dda;

static t_dda	dda_horizontal(t_vec2f pos, float angle)
{
	t_dda	out;

	if (180 > angle  && angle > 0)
	{
		out.point.y = round(pos.y) - 1;
		out.pad.y = -1;
	}
	else
	{
		out.point.y = round(pos.y) + 1;
		out.pad.y = 1;
	}
	out.point.x = pos.x + (pos.y - out.point.y) / tanf(angle);
	out.pad.x = 1 / tanf(angle);
	return (out);
}

static t_dda	dda_vertical(t_vec2f pos, float angle)
{
	t_dda	out;

	if (270 < angle  && angle > 90)
	{
		out.point.x = round(pos.x) - 1;
		out.pad.x = 1;
	}
	else
	{
		out.point.x = round(pos.x) + 1;
		out.pad.x = -1;
	}
	out.point.y = pos.y + (pos.x - out.point.x) * tanf(angle);
	out.pad.y = 1 * tanf(angle);
	return (out);
}

float	dda_checker(t_vec2f pos, float angle, t_map map)
{
	static bool start = false;;

	t_dda	horizontal;
	t_dda	vertical;

	t_vec2f	new_h;
	t_vec2f	new_v;

	float	dist_h;
	float	dist_v;

	float	total_len;

	angle =  (angle * M_PI / 180.0);
	total_len = 0;

	horizontal = dda_horizontal(pos, angle);
	vertical = dda_vertical(pos, angle);
	while (map.data[(int)pos.y][(int)pos.x] != '1')
	{
		if (start == false)
		{
			start = true;
			printf("start\n");
		}
		new_h = add_vec2f(pos, horizontal.pad);
		new_v = add_vec2f(pos, vertical.pad);

		dist_h = vec2f_dist(pos, new_h);
		dist_v = vec2f_dist(pos, new_v);
		if (dist_h < dist_v)
		{
			pos = add_vec2f(pos, new_h);
			pos = new_h;
			total_len += dist_h;
		}
		else
		{
			pos = add_vec2f(pos, new_v);
			pos = new_v;
			total_len += dist_v;
		}
	}
	if (start == true)
	{
		start = false;
		printf("end\n");
	}

	return (total_len);
}
