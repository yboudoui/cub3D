/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:51:33 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/07 16:29:54 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	init(t_screen *screen)
{
	static t_data	data;

	data = data_init(screen, g_floor, g_ceilling, (char **)g_map);
	screen->data = &data;
	player_init(&data, (t_vec2f){2, 2}, EAST);
	init_minimap(screen);
}

void	stop(t_screen *screen)
{
	free(precompute(NULL).angle);
	data_destroy(screen->data);
	screen_destroy(screen);
}

int	main(void)
{
	t_screen	*screen;

	screen = screen_create("cub3D", (t_vec2){WIDTH, HEIGHT});
	if (NULL == screen)
		return (-2);
	init(screen);
	mlx_loop_hook(screen->mlx->mlx, draw, screen);
	mlx_loop(screen->mlx->mlx);
	return (stop(screen), 0);
}
