/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:51:33 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/05 18:29:00 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define WIDTH 1200
#define HEIGHT 800

const t_color	g_floor = {.raw = 0x0000FF};
const t_color	g_ceilling = {.raw = 0xFF00FF};

char			*g_map[] = {
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
	if (false == update_state(screen))
		return (-1);
	draw_image(screen);
	mlx_put_image_to_window(screen->mlx->mlx, screen->mlx->win,
		screen->img->data, 0, 0);
	return (0);
}

t_data	data_init(t_screen *screen, t_color ceiling, t_color ground)
{
	t_data	data;

	data.map = (t_map){(char **)g_map, (t_vec2){10, 12}};
/*
	data.texture[NORTH] = image_new_xpm(screen->mlx, "./texture/north.xpm");
	data.texture[SOUHT] = image_new_xpm(screen->mlx, "./texture/south.xpm");
	data.texture[EAST] = image_new_xpm(screen->mlx, "./texture/east.xpm");
	data.texture[WEST] = image_new_xpm(screen->mlx, "./texture/weast.xpm");
*/
	data.texture[NORTH] = image_new_xpm(screen->mlx, "./texture/small/p.xpm");
	data.texture[SOUHT] = image_new_xpm(screen->mlx, "./texture/small/p.xpm");
	data.texture[EAST] = image_new_xpm(screen->mlx, "./texture/small/p.xpm");
	data.texture[WEST] = image_new_xpm(screen->mlx, "./texture/small/p.xpm");
	data.nmap = normal_map_create(screen->mlx, "./texture/small/p.normal_map.xpm");

	data.floor_ceilling = image_env(screen, ceiling, ground);
	data.walls = ft_calloc(screen->size.x, sizeof(t_dda));
	return (data);
}

int	main(void)
{
	static t_precompute	pre;
	t_screen			*screen;
	t_data				data;

	screen = screen_create("cub3D", (t_vec2){WIDTH, HEIGHT});
	if (NULL == screen)
		return (-2);
	data = data_init(screen, g_floor, g_ceilling);
	data.player = (t_player){
		.pos = (t_vec2f){2, 2},
		.view = 0,
		.fov = 60,
		.mouse_speed = 0.5,
	};
	pre = precompute_tan(data.player.fov, WIDTH);
	precompute(&pre);
	data.pre = pre;
	screen->data = &data;
	init_minimap(screen);
	mlx_loop_hook(screen->mlx->mlx, draw, screen);
	mlx_loop(screen->mlx->mlx);
	return (screen_destroy(screen), 0);
}
