/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:34:07 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/06 21:40:37 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	texture_destroy(void *texture)
{
	t_texture_	*data;
	int			index;

	data = texture;
	if (data == NULL)
		return ;
	index = -1;
	while (++index < data->size.x)
		free(data->column[index]);
	free(data->column);
	free(data);
}

t_texture_	*texture_create(t_image *src)
{
	t_vec2		index;
	t_texture_	*out;

	out = ft_calloc(1, sizeof(t_texture));
	if (out)
		out->column = ft_calloc(src->size.x, sizeof(t_color *));
	if (out == NULL || out->column == NULL)
		return (texture_destroy(out), NULL);
	out->size = src->size;
	index.x = -1;
	while (++index.x < src->size.x)
	{
		out->column[index.x] = ft_calloc(src->size.y, sizeof(t_color));
		if (out->column[index.x] == NULL)
			return (texture_destroy(out), NULL);
		index.y = -1;
		while (++index.y < src->size.y)
			out->column[index.x][index.y] = image_get_pixel(src, index).color;
	}
	return (out);
}

t_texture_	*texture_init(t_mlx *mlx, char *path)
{
	t_image		*src;
	t_texture_	*out;

	src = image_new_xpm(mlx, path);
	if (src == NULL)
		return (NULL);
	out = texture_create(src);
	return (delete_image(src), out);
}
