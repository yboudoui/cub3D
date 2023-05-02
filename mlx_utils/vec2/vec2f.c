/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:27:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/02 13:56:07 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"

t_vec2	vec2f_floor(t_vec2f v)
{
	return ((t_vec2){
		.x = floor(v.x),
		.y = floor(v.y),
	});
}

bool	vec2f_in_range(t_vec2f v, t_vec2f min, t_vec2f max)
{
	if (min.x > v.x || v.x > max.x)
		return (false);
	if (min.y > v.y || v.y > max.y)
		return (false);
	return (true);
}

t_vec2f	vec2f_add(t_vec2f a, t_vec2f b)
{
	t_vec2f	out;

	out.x = a.x + b.x;
	out.y = a.y + b.y;
	return (out);
}

#include <stdio.h>
float	vec2f_dist(t_vec2f a, t_vec2f b)
{
	t_vec2f	dist;

	dist.x = fabsf(a.x - b.x);
	dist.y = fabsf(a.y - b.y);
	return (hypotf(dist.x, dist.y));
}

t_vec2f	vec2f_normalize(t_vec2f v)
{
	float	dist;

	dist = vec2f_dist((t_vec2f){0,0}, v);
	return ((t_vec2f){
		.x = v.x / dist,
		.y = v.y / dist,
	});
}

t_vec2f	vec2f_scale(t_vec2f v, float scale)
{
	return ((t_vec2f){
		.x = v.x * scale,
		.y = v.y * scale,
	});
}
