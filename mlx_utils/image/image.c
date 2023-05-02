/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:17:12 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/02 19:33:34 by yboudoui         ###   ########.fr       */
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
	out->data = mlx_new_image(out->mlx, size.x, size.y);
	out->addr = mlx_get_data_addr(out->data,
			&out->bits_per_pixel,
			&out->line_length,
			&out->endian);
	image_clear(out, (t_color){.raw = 0x000000});
	return (out);
}

t_image	*image_new_xpm(t_mlx *data, char *path)
{
	t_image	*out;

	out = ft_calloc(1, sizeof(t_image));
	if (NULL == out)
		return (NULL);
	out->mlx = data->mlx;
	out->data = mlx_xpm_file_to_image(out->mlx, path, &out->size.x, &out->size.y);
	out->addr = mlx_get_data_addr(out->data,
			&out->bits_per_pixel,
			&out->line_length,
			&out->endian);
	return (out);
}

void	image_clear(t_image *img, t_color color)
{
	size_t	size;

	size = (img->size.x - 1) * (img->bits_per_pixel / 8);
	size += (img->size.y - 1) * (img->line_length);
	ft_memset(img->addr, color.raw, size);
}

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

inline void	image_put_to_image(t_image *src, t_image *dest)
{
	t_pixel	index;
	t_pixel	tmp;

	index = (t_pixel){
		.coord = (t_vec2){-1, -1},
	};
	while (++index.coord.y < src->size.y)
	{
		index.coord.x = -1;
		while (++index.coord.x < src->size.x)
		{
			tmp = image_get_pixel(src, index.coord);
	//		printf("%d\n", tmp.color.chanel[TRANSPARENCY]);
			index.color = interpolate_color(
				image_get_pixel(dest, index.coord).color,
	0.5,//			(float)(255.0 / tmp.color.chanel[TRANSPARENCY]),
				tmp.color
			);
//			index.color.chanel[TRANSPARENCY] = 0;
			image_put_pixel(dest, index);
		}
	}
}

/*

inline void	image_put_to_image(t_image *src, t_image *dest)
{
	int	index;

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
*/
