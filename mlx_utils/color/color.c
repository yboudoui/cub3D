/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 13:28:23 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/05 17:54:14 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_color	create_trgb(t_chanel t, t_chanel r, t_chanel g, t_chanel b)
{
	t_color	out;

	out.chanel[BLUE] = b;
	out.chanel[GREEN] = g;
	out.chanel[RED] = r;
	out.chanel[TRANSPARENCY] = t;
	return (out);
}

t_color	color_create_raw(unsigned int raw)
{
	return ((t_color){.raw = raw});
}

void	color_brightness(t_color *c, float brightness)
{
	(*c).chanel[0] = (*c).chanel[0] * brightness;
	(*c).chanel[1] = (*c).chanel[1] * brightness;
	(*c).chanel[2] = (*c).chanel[2] * brightness;
	(*c).chanel[3] = (*c).chanel[3] * brightness;
}

void	color_contrast(t_color *c, float contrast)
{
	int	coefficient;

	coefficient = 128;
	(*c).chanel[0] = (contrast * (*c).chanel[0] - coefficient) + coefficient;
	(*c).chanel[1] = (contrast * (*c).chanel[1] - coefficient) + coefficient;
	(*c).chanel[2] = (contrast * (*c).chanel[2] - coefficient) + coefficient;
	(*c).chanel[3] = (contrast * ((*c).chanel[3] - coefficient)) + coefficient;
}

t_color	interpolate_color(t_color a, float t, t_color b)
{
	t_color	out;

	out.chanel[0] = a.chanel[0] + (b.chanel[0] - a.chanel[0]) * t ;
	out.chanel[1] = a.chanel[1] + (b.chanel[1] - a.chanel[1]) * t ;
	out.chanel[2] = a.chanel[2] + (b.chanel[2] - a.chanel[2]) * t ;
	out.chanel[3] = a.chanel[3] + (b.chanel[3] - a.chanel[3]) * t ;
	return (out);
}
