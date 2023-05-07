/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:51:33 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/07 18:58:58 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	draw(t_screen *screen)
{
	if (false == update_state(screen))
		return (-1);
	draw_image(screen);
	mlx_put_image_to_window(screen->mlx->mlx, screen->mlx->win,
		screen->img->data, 0, 0);
	return (0);
}

bool	init(t_screen *screen, t_config config)
{
	if (data_init(screen, config) == false)
		return (false);
	return (player_init(screen->data, config.player_pos, EAST));
}

void	stop(t_screen *screen)
{
	free(precompute(NULL).angle);
	data_destroy(screen->data);
	screen_destroy(screen);
}

int	main(int argc, char **argv)
{
	t_screen	*screen;
	t_config	config;

	if (argc != 2)
		return (ft_error("Error\nWrong number of arguments\n"), -1);
	if (parser(argv[1], &config) == false)
		return (free_map(&config), -1);
	screen = screen_create("cub3D", (t_vec2){WIDTH, HEIGHT});
	if (NULL == screen)
		return (-2);
	if (init(screen, config))
	{
		mlx_loop_hook(screen->mlx->mlx, draw, screen);
		mlx_loop(screen->mlx->mlx);
	}
	free_map(&config);
	return (stop(screen), 0);
}
