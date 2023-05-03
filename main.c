/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:51:33 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/03 13:33:56 by kdhrif           ###   ########.fr       */
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
"1000001001",
"1000101001",
"1000001001",
"1000001001",
"1000111111",
"1000000001",
"1000000001",
"1111111111",
NULL,
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

int	main(int argc, char **argv)
{
	t_screen	*screen;
	t_data		data;

	if (argc != 2)
	{
		ft_error("Error\nWrong number of arguments\n");
		return (-1);
	}
	if (parser(argv[1], &data.config) == false)
		return (-1);
	screen = screen_create("cub3D", vec2(WIDTH, HEIGHT));
	if (NULL == screen)
		return (-2);
	data.map = (t_map){(char **)map, vec2(10, 12)};
	data.mini_map = image_new(screen->mlx, add_vec2(mul_vec2(data.map.size, vec2(16, 16)), vec2(1, 1)));
	data.dda_debugger = image_new(screen->mlx, add_vec2(mul_vec2(data.map.size, vec2(16, 16)), vec2(1, 1)));
	data.texture.north = image_new_xpm(screen->mlx, "./texture/wall.xpm");
	data.player = (t_player){
			.pos = (t_vec2f){1, 1.2},
			//.view = 358.5,
			.view = 230,
			.fov = 60,
			.mouse_speed = 0.5
			/* .mouse_speed = 56 */
		};
	data.walls = ft_calloc(screen->size.x, sizeof(t_dda));
	screen->data = &data;
	mlx_loop_hook(screen->mlx->mlx, draw, screen);
	mlx_loop(screen->mlx->mlx);
	return (screen_destroy(screen), 0);
}
