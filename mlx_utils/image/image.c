/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:17:12 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/06 21:39:51 by yboudoui         ###   ########.fr       */
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

t_image	*image_new(t_mlx *data, t_vec2 size)
{
	t_image	*out;

	out = ft_calloc(1, sizeof(t_image));
	if (NULL == out)
		return (NULL);
	out->mlx = data->mlx;
	out->size = size;
	out->center = (t_vec2){size.x / 2, size.y / 2};
	out->data = mlx_new_image(out->mlx, size.x, size.y);
	out->addr = mlx_get_data_addr(out->data,
			&out->bits_per_pixel,
			&out->line_length,
			&out->endian);
	return (image_clear(out, (t_color){.raw = 0x000000}), out);
}

void	image_clear(t_image *img, t_color color)
{
	size_t	size;

	size = (img->size.x - 1) * (img->bits_per_pixel / 8);
	size += (img->size.y - 1) * (img->line_length);
	ft_memset(img->addr, color.raw, size);
}

inline void	image_put_to_image(t_image *src, t_image *dest)
{
	int	index;

	if (src == NULL || dest == NULL)
		return ;
	index = 0;
	while (index < src->size.y)
	{
		ft_memcpy(
			&dest->addr[index * dest->line_length],
			&src->addr[index * src->line_length],
			src->line_length);
		index += 1;
	}
}
