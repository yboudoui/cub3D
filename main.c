/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:51:33 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/26 18:04:49 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define WIDTH 1200
#define HEIGHT 800

char *map[] = {
"1111111111",
"1000000001",
"1000000001",
"1000000001",
"1000000001",
"1000000001",
"1000000001",
"1000000001",
"1000111001",
"1000000001",
"1000000001",
"1111111111",
};

int	draw(t_screen *screen)
{
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
	t_data		data;

	data = (t_data){
		.map = (char **)map,
		.player = (t_player){
			.pos = (t_vec2f){3.5, 2.2},
			.view = 90.0,
			.fov = 60,
			.mouse_speed = 56,
		}
	};

	screen = screen_create("cub3D", WIDTH, HEIGHT);
	if (NULL == screen)
		return (-2);
	screen->data = &data;
	mlx_loop_hook(screen->mlx->mlx, draw, screen);
	mlx_loop(screen->mlx->mlx);
	return (screen_destroy(screen), 0);
}
