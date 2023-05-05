/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:16:09 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/05 18:58:01 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	deg_to_rad(float deg)
{
	return (deg * M_PI / 180);
}

t_precompute	precompute_tan(float fov, int screen_width)
{
	t_precompute	out;
	int				index;
	float			angle;
	float			ratio;

	ratio = 360.0 / fov;
	out.pad = fov / screen_width;
	out.size = screen_width * ratio;
	out.tan = ft_calloc(out.size - 1, sizeof(float));
	out.cos = ft_calloc(out.size - 1, sizeof(float));
	out.sin = ft_calloc(out.size - 1, sizeof(float));
//protect calloc error!!
	index = -1;
	angle = 0;
	while (++index < screen_width * ratio)
	{
		out.tan[index] = tanf(deg_to_rad(angle));
		out.cos[index] = cosf(deg_to_rad(angle));
		out.sin[index] = sinf(deg_to_rad(angle));
		angle += out.pad;
	}
	out.limit[NORTH] = 0;
	out.limit[EAST] = out.size / 4;
	out.limit[SOUHT] = out.size / 2;
	out.limit[WEST] = (out.size / 4) * 3;
	return (out);
}

t_precompute	precompute(t_precompute *in)
{
	static t_precompute	*out;

	if (out == NULL)
		out = in;
	return (*out);
}
