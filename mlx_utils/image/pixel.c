/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:19:29 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/06 16:31:03 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

inline void	image_put_pixel(t_image *img, t_pixel pixel)
{
	char	*dst;

	if (pixel.coord.x < 0 || pixel.coord.x >= img->size.x)
		return ;
	if (pixel.coord.y < 0 || pixel.coord.y >= img->size.y)
		return ;
	dst = img->addr;
	pixel.coord.x *= (img->bits_per_pixel / 8);
	pixel.coord.y *= (img->line_length);
	dst += (int)(pixel.coord.y + pixel.coord.x);
	*(unsigned int *)dst = pixel.color.raw;
}

inline t_pixel	image_get_pixel(t_image *img, t_vec2 pos)
{
	t_pixel	out;
	char	*dst;

	out = (t_pixel){0};
	if (pos.x < 0 || pos.x >= img->size.x)
		return (out);
	if (pos.y < 0 || pos.y >= img->size.y)
		return (out);
	dst = img->addr;
	pos.x *= (img->bits_per_pixel / 8);
	pos.y *= (img->line_length);
	dst += (int)(pos.y + pos.x);
	out.color.raw = *(unsigned int *)dst;
	return (out);
}
