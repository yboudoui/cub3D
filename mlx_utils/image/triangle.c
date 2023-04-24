/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:56:39 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/24 17:22:46 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include <limits.h>

static bool	custom_bresenham_data_update(t_bresenham_data *in)
{
	t_vec2	out;
	bool	stop;

	stop = false;
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
		stop = true;
	}
	in->current.coord.x += out.x;
	in->current.color = interpolate_color(
			in->start.color,
			in->color_interpolation.current,
			in->end.color
			);
	in->color_interpolation.current += in->color_interpolation.pad;
	return (stop);
}

static bool	draw_line_step(t_bresenham_data *brd)
{
	if (0
		|| brd->start.coord.y >= brd->current.coord.y
		|| brd->current.coord.y > brd->end.coord.y
	)
		return (brd->current.coord.y += 1, false);
	while (1)
		if (custom_bresenham_data_update(brd))
			break ;
	return (brd->current.coord.y += 1, true);
}

static void	init_triangle(t_bresenham_data data[3], t_pixel points[3], int min)
{
	int	index;

	data[0] = bresenham_data_init(points[0], points[1]);
	data[1] = bresenham_data_init(points[1], points[2]);
	data[2] = bresenham_data_init(points[2], points[0]);
	index = 0;
	while (index < 3)
		data[index++].current.coord.y = min;
}

static void	tri_max_iteration(t_pixel points[3], int *min, int *max)
{
	size_t	index;

	index = 0;
	*min = INT_MAX;
	*max = INT_MIN;
	while (index < 3)
	{
		if (*min > points[index].coord.y)
			*min = points[index].coord.y;
		if (*max < points[index].coord.y)
			*max = points[index].coord.y;
		index++;
	}
}

void	image_put_triangle(t_image *img, t_pixel points[3])
{
	t_bresenham_data	brd[3];
	int					min;
	int					max;
	t_pixel				*buffer;
	int					*index;

	tri_max_iteration(points, &min, &max);
	init_triangle(brd, points, min);
	while (min <= max)
	{
		buffer = (t_pixel [2]){0};
		index = (int [3]){3, 0};
		while (index[0]-- && index[1] < 4)
			if (draw_line_step(&brd[index[0]]))
				buffer[index[2]++] = brd[index[0]].current;
		image_put_line(img, buffer[0], buffer[1]);
		min++;
	}
}
