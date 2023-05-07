/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:27:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/05 18:51:15 by yboudoui         ###   ########.fr       */
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
	return ((t_vec2f){
		.x = a.x + b.x,
		.y = a.y + b.y,
	});
}

t_vec2f	vec2f_mul(t_vec2f a, t_vec2f b)
{
	return ((t_vec2f){
		.x = a.x * b.x,
		.y = a.y * b.y,
	});
}

float	cosin_similarity(t_vec2f a, t_vec2f b)
{
	float	dot;
	float	abs;

	a = vec2f_normalize(a);
	b = vec2f_normalize(b);
	dot = vec2f_dot_produc(a, b);
	abs = vec2f_size(a) * vec2f_size(b);
	return (dot / abs);
}
