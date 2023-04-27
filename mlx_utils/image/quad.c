/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:55:05 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/27 16:51:10 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

inline void	image_put_quad(t_image *img, t_quad quad)
{
	image_put_triangle(img, (t_pixel [3]){
		quad.point[0][0],
		quad.point[0][1],
		quad.point[1][1],
	});
	image_put_triangle(img, (t_pixel [3]){
		quad.point[1][0],
		quad.point[0][0],
		quad.point[1][1],
	});
}

inline void	image_put_empty_quad(t_image *img, t_quad quad)
{
	image_put_line(img, quad.point[0][0], quad.point[0][1]);
	image_put_line(img, quad.point[0][0], quad.point[1][0]);
	image_put_line(img, quad.point[1][1], quad.point[0][1]);
	image_put_line(img, quad.point[1][1], quad.point[1][0]);
}

t_quad	rectangle(t_vec2 pos, t_vec2 size, t_color color)
{
	t_quad	rect;

	rect.point[0][0] = pixel(vec2(pos.x, pos.y), color);
	rect.point[0][1] = pixel(vec2(pos.x, pos.y + size.y), color);
	rect.point[1][0] = pixel(vec2(pos.x + size.x, pos.y), color);
	rect.point[1][1] = pixel(vec2(pos.x + size.x, pos.y + size.y), color);
	return (rect);
}
