/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:25:11 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/28 10:48:57 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"

t_vec2	vec2(int x, int y)
{
	return ((t_vec2){x, y});
}

int	cmp(int a, int b)
{
	return ((a > b) - (a < b));
}

t_vec2	cmp_vec2(t_vec2 a, t_vec2 b)
{
	t_vec2	out;

	out.x = cmp(a.x, b.x);
	out.y = cmp(a.y, b.y);
	return (out);
}

t_vec2	substract_vec2(t_vec2 a, t_vec2 b)
{
	t_vec2	out;

	out.x = a.x - b.x;
	out.y = a.y - b.y;
	return (out);
}

t_vec2	mul_vec2(t_vec2 a, t_vec2 b)
{
	t_vec2	out;

	out.x = a.x * b.x;
	out.y = a.y * b.y;
	return (out);
}

t_vec2	add_vec2(t_vec2 a, t_vec2 b)
{
	t_vec2	out;

	out.x = a.x + b.x;
	out.y = a.y + b.y;
	return (out);
}

bool	vec2i_in_range(t_vec2 v, t_vec2 min, t_vec2 max)
{
	if (min.x > v.x || v.x > max.x)
		return (false);
	if (min.y > v.y || v.y > max.y)
		return (false);
	return (true);
}
