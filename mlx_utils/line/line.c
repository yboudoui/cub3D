/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:13:05 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/05 18:36:48 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"
#include <stdlib.h>

inline static void	set_interpolation(t_bresenham_data *in)
{
	int	size;

	size = abs(in->start.coord.x - in->end.coord.x);
	if (size < abs(in->start.coord.y - in->end.coord.y))
		size = abs(in->start.coord.y - in->end.coord.y);
	in->color_interpolation.pad = 1.0 / size;
	in->color_interpolation.current = 0;
}

inline t_bresenham_data	bresenham_data_init(t_pixel start, t_pixel end)
{
	t_bresenham_data	out;

	if (start.coord.y > end.coord.y)
	{
		out.start = end;
		out.end = start;
	}
	else
	{
		out.start = start;
		out.end = end;
	}
	out.current = out.start;
	out.derivative = (t_vec2){
		.x = abs(out.end.coord.x - out.start.coord.x),
		.y = -abs(out.end.coord.y - out.start.coord.y)
	};
	out.slop = cmp_vec2(out.end.coord, out.start.coord);
	out.error = out.derivative.x + out.derivative.y;
	set_interpolation(&out);
	return (out);
}

inline void	bresenham_data_update(t_bresenham_data *in)
{
	t_vec2	out;

	out = (t_vec2){0};
	in->difference = (in->error * 2);
	if (in->difference > in->derivative.y)
	{
		in->error += in->derivative.y;
		out.x = in->slop.x;
	}
	if (in->difference < in->derivative.x)
	{
		in->error += in->derivative.x;
		out.y = in->slop.y;
	}
	in->current.coord = vec2_add(in->current.coord, out);
	in->current.color = interpolate_color(
			in->start.color,
			in->color_interpolation.current,
			in->end.color
			);
	in->color_interpolation.current += in->color_interpolation.pad;
}
