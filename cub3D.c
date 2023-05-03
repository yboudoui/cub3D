/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:16:09 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/03 13:26:48 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_precompute	precompute_tan(float fov, int screen_width)
{
	t_precompute	out;
	int				index;
	float			angle;
	float			ratio;

	ratio = 360.0 / fov;
	out.pad = fov / screen_width;
	out.size = screen_width * ratio;
	out.tan_arr = ft_calloc(out.size - 1, sizeof(float));
//	if (out.tan_array == NULL)
	index = -1;
	angle = 0;
	while (++index < screen_width * ratio)
	{
		out.tan_arr[index] = tanf(deg_to_rad(angle));
		angle += out.pad;
	}
	out.limit[NORTH] = 0;
	out.limit[EAST] = out.size / 4;
	out.limit[SOUHT] = out.size / 2;
	out.limit[WEST] = (out.size / 4) * 3;
	return (out);
}
