/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:51:33 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/02 15:29:17 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define WIDTH 1280
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

int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

t_vec2 calculate_map_size(char **map)
{
	t_vec2	size;
	int		i;

	size = vec2(0, 0);
	i = 0;
	while (map[i])
	{
		size.x = ft_max(size.x, ft_strlen(map[i]));
		size.y += 1;
		i += 1;
	}
	return (size);
}

int	main(void)
{
	t_screen	*screen;
	t_data		data;

	screen = screen_create("cub3D", vec2(WIDTH, HEIGHT));
	if (NULL == screen)
		return (-2);
	/* data.map = (t_map){(char **)map, vec2(10, 12)}; */
	data.map = (t_map){(char **)map, calculate_map_size(map), mul_vec2(calculate_map_size(map), vec2(TILE_SIZE, TILE_SIZE))}; // dynamic map size parsing
	data.mini_map = image_new(screen->mlx, add_vec2(mul_vec2(data.map.size, vec2(16, 16)), vec2(1, 1)));
	data.dda_debugger = image_new(screen->mlx, add_vec2(mul_vec2(data.map.size, vec2(16, 16)), vec2(1, 1)));
	data.player = (t_player){
			.pos = (t_vec2f){5, 3},
			.tiled_pos = (t_vec2f){5 * 64, 3 * 64},
			.view = 280.397461,
			.fov = 60,
			.mouse_speed = 0.5
			/* .mouse_speed = 56 */
		};
	data.walls = ft_calloc(screen->size.x, sizeof(t_wall));
	screen->data = &data;
	mlx_loop_hook(screen->mlx->mlx, draw, screen);
	mlx_loop(screen->mlx->mlx);
	return (screen_destroy(screen), 0);
}
