/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:55:05 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/24 15:38:31 by yboudoui         ###   ########.fr       */
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
