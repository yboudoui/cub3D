/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:17:12 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/27 14:43:37 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	delete_image(t_image *img)
{
	if (NULL == img)
		return ;
	mlx_destroy_image(img->mlx, img->data);
	free(img);
}

t_image	*image_new(t_mlx *data, int width, int height)
{
	t_image	*out;

	out = ft_calloc(1, sizeof(t_image));
	if (NULL == out)
		return (NULL);
	out->mlx = data->mlx;
	out->height = height;
	out->width = width;
	out->data = mlx_new_image(out->mlx, width, height);
	out->addr = mlx_get_data_addr(out->data,
			&out->bits_per_pixel,
			&out->line_length,
			&out->endian);
	return (out);
}

void	image_clear(t_image *img, t_color color)
{
	size_t	size;

	size = (img->width - 1) * (img->bits_per_pixel / 8);
	size += (img->height - 1) * (img->line_length);
	ft_memset(img->addr, color.raw, size);
}

inline void	image_put_pixel(t_image *img, t_pixel pixel)
{
	char	*dst;

	if (pixel.coord.x < 0 || pixel.coord.x >= img->width)
		return ;
	if (pixel.coord.y < 0 || pixel.coord.y >= img->height)
		return ;
	dst = img->addr;
	pixel.coord.x *= (img->bits_per_pixel / 8);
	pixel.coord.y *= (img->line_length);
	dst += (int)(pixel.coord.y + pixel.coord.x);
	*(unsigned int *)dst = pixel.color.raw;
}
