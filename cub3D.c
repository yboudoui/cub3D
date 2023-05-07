/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:16:09 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/07 18:45:45 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	deg_to_rad(float deg)
{
	return (deg * M_PI / 180);
}

void	precompute_init(float fov, int screen_width)
{
	static t_precompute	out;
	int					index;
	float				ratio;

	ratio = 360.0 / fov;
	out.pad = fov / screen_width;
	out.size = (screen_width * ratio) - 1;
	out.angle = ft_calloc(out.size, sizeof(struct s_angle));
	if (out.angle == NULL)
		return ;
	index = -1;
	while (++index < out.size)
	{
		out.angle[index].tan = tanf(deg_to_rad(index * out.pad));
		out.angle[index].cos = cosf(deg_to_rad(index * out.pad));
		out.angle[index].sin = sinf(deg_to_rad(index * out.pad));
	}
	out.limit[NORTH] = 0;
	out.limit[EAST] = out.size / 4;
	out.limit[SOUHT] = out.size / 2;
	out.limit[WEST] = (out.size / 4) * 3;
	precompute(&out);
}

t_precompute	precompute(t_precompute *in)
{
	static t_precompute	*out;

	if (in)
		out = in;
	if (out)
		return (*out);
	return ((t_precompute){0});
}

int	y_wrap_angle(int angle)
{
	int	angle_mod;
	int	fiel_of_view;

	fiel_of_view = precompute(NULL).size;
	angle_mod = angle % fiel_of_view;
	if (angle_mod < 0)
		angle_mod += fiel_of_view;
	return (angle_mod);
}
