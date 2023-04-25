/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:26:37 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/25 18:59:34 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_dda {
	t_vec2f	intersection;
	t_vec2f	incrementation;
}	t_dda;

static t_dda	dda_horizontal(t_vec2f pos, float angle, int cube_size)
{
	t_dda	out;

	if (180 > angle  && angle > 0)
	{
		out.intersection.y = (round(pos.y / cube_size) * cube_size) - 1;
		out.incrementation.y = -cube_size;
	}
	else
	{
		out.intersection.y = (round(pos.y / cube_size) * cube_size) + cube_size;
		out.incrementation.y = cube_size;
	}
	out.intersection.x = pos.x + (pos.y - out.intersection.y) / tan(angle);
	out.incrementation.x = cube_size / tan(angle);
	return (out);
}

static t_dda	dda_vertical(t_vec2f pos, float angle, int cube_size)
{
	t_dda	out;

	if (270 < angle  && angle > 90)
	{
		out.intersection.x = (round(pos.x / cube_size) * cube_size) - 1;
		out.incrementation.x = cube_size;
	}
	else
	{
		out.intersection.x = (round(pos.x / cube_size) * cube_size) + cube_size;
		out.incrementation.x = -cube_size;
	}
	out.intersection.y = pos.y + (pos.x - out.intersection.x) * tan(angle);
	out.incrementation.y = cube_size * tan(angle);
	return (out);
}

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

float	dda_checker(t_vec2f pos, float angle, char **map, int cube_size)
{
	t_dda	horizontal;
	t_dda	vertical;

	t_vec2f	new_h;
	t_vec2f	new_v;

	float	dist_h;
	float	dist_v;

	float	total_len;

	angle =  (angle * M_PI / 180.0);
	pos.x /= cube_size;
	pos.y /= cube_size;
	total_len = 0;

	horizontal = dda_horizontal(pos, angle, cube_size);
	vertical = dda_vertical(pos, angle, cube_size);
	while (map[(int)pos.y][(int)pos.x] != '1')
	{
		new_h = add_vec2f(pos, horizontal.incrementation);
		new_v = add_vec2f(pos, vertical.incrementation);

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
		pos.x /= cube_size;
		pos.y /= cube_size;
	}
	return (total_len);
}
