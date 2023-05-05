/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:10:46 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/05 17:17:34 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

t_vec3f	color_to_vec3f(t_color color)
{
	return ((t_vec3f){
		.x = ((color.chanel[RED] / 255) * 2) - 1,
		.y = ((color.chanel[GREEN] / 255) * 2) - 1,
		.z = ((color.chanel[BLUE] / 255) * 2) - 1,
	});
}

t_normal_map	normal_map_create(t_mlx *mlx, char *img_path)
{
	t_vec2			index;
	t_pixel			px;
	t_image			*tmp;
	t_normal_map	out;

	tmp = image_new_xpm(mlx, img_path);
	out.map = ft_calloc(tmp->size.y, sizeof(t_vec3f *));
	index = vec2(-1);
	while (++index.y < tmp->size.y)
	{
		index.x = -1;
		out.map[index.y] = ft_calloc(tmp->size.x, sizeof(t_vec3f));
		while (++index.x < tmp->size.x)
		{
			px = image_get_pixel(tmp, index);
			out.map[index.y][index.x] = color_to_vec3f(px.color);
		}
	}
	return (delete_image(tmp), out);
}
