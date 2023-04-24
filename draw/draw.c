/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:21:13 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/24 17:51:49 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static inline void	drawer(t_screen *screen, t_quad quad)
{
	int	mode;

	mode = 1;
	if (mode == 1)
		image_put_quad(screen->img, quad);
	else
		image_put_empty_quad(screen->img, quad);
}

void	draw_image(t_screen *screen)
{
	t_quad	quad;
	t_color	a;
	t_color	b;

	quad = (t_quad){0};
	a = create_trgb(1, 255, 0, 0);
	b = create_trgb(1, 0, 0, 255);

	quad.point[0][0] = (t_pixel){
		.coord = (t_vec2){50, 50},
		.color.raw = 0x00FF00
	};
	quad.point[0][1] = (t_pixel){
		.coord = (t_vec2){200, 400},
		.color.raw = 0xFFFFFF
	};
	quad.point[1][0] = (t_pixel){
		.coord = (t_vec2){750, 50},
		.color = b
	};
	quad.point[1][1] = (t_pixel){
		.coord = (t_vec2){750, 590},
		.color = a
	};

	const t_color	g_BLACK = (t_color){.raw = 0};
	image_clear(screen->img, g_BLACK);
	drawer(screen, quad);
}
