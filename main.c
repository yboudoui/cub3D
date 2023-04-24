/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:51:33 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/24 17:19:50 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define WIDTH 800
#define HEIGHT 640

int	draw(t_screen *screen)
{
	screen->center = screen->mlx->event.mouse.pos;
	if (false == update_state(screen))//	here update mouse + keyboard state
		return (-1);
	draw_image(screen);
	mlx_put_image_to_window(screen->mlx->mlx, screen->mlx->win,
		screen->img->data, 0, 0);
	return (0);
}

int	main(void)
{
	t_screen	*screen;

	screen = screen_create("cub3D", WIDTH, HEIGHT);
	if (NULL == screen)
		return (-2);
	mlx_loop_hook(screen->mlx->mlx, draw, screen);
	mlx_loop(screen->mlx->mlx);
	return (screen_destroy(screen), 0);
}
