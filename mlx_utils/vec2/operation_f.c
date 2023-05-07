/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:41:11 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/05 18:48:35 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"

float	vec2f_dist(t_vec2f a, t_vec2f b)
{
	t_vec2f	dist;

	dist.x = fabsf(a.x - b.x);
	dist.y = fabsf(a.y - b.y);
	return (hypotf(dist.x, dist.y));
}

float	vec2f_size(t_vec2f v)
{
	return (vec2f_dist((t_vec2f){0, 0}, v));
}

t_vec2f	vec2f_normalize(t_vec2f v)
{
	float	dist;

	dist = vec2f_dist((t_vec2f){0, 0}, v);
	if (dist == 0)
		return ((t_vec2f){0, 0});
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

float	vec2f_dot_produc(t_vec2f a, t_vec2f b)
{
	return ((a.x * b.x) + (a.y * b.y));
}
