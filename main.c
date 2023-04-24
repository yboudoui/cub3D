/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:51:33 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/24 21:03:58 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define WIDTH 800
#define HEIGHT 640

char map[][] = {
{1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,1},
{1,0,0,0,1,0,0,0,1},
{1,0,0,0,1,0,1,0,1},
{1,0,0,0,1,0,0,0,1},
{1,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1},
};

t_vec2f	player_pos = (t_vec2){1,1};
float	player_view = 290;

#define CUBE_SIZE 64

typedef struct s_dda {
	t_vec2f	intersection;
	t_vec2f	incrementation;
}	t_dda;

t_dda	dda_horizontal(t_vec2f player_pos, float angle_view)
{
	t_dda	out;

	if (angle_view > 180 && angle_view < 0)
	{
		out.intersection.y = (round(player_pos.y / CUBE_SIZE) * CUBE_SIZE) - 1;
		out.incrementation.y = -CUBE_SIZE;
	}
	else
	{
		out.intersection.y = (round(player_pos.y / CUBE_SIZE) * CUBE_SIZE) - CUBE_SIZE;
		out.incrementation.y = CUBE_SIZE;
	}
	out.intersection.x = player_pos.x + (player_pos.y - out.y) / tan(angle_view);
	out.incrementation.x = CUBE_SIZE / tan(angle_view);
	return (out);
}

t_dda	dda_vertical(t_vec2f player_pos, float angle_view)
{
	t_dda	out;

	if (angle_view > 90 && angle_view < 270)
	{
		out.intersection.x = (round(player_pos.x / CUBE_SIZE) * CUBE_SIZE) - CUBE_SIZE;
		out.incrementation.x = CUBE_SIZE;
	}
	else
	{
		out.intersection.x = (round(player_pos.x / CUBE_SIZE) * CUBE_SIZE) - 1;
		out.incrementation.x = -CUBE_SIZE;
	}
	out.intersection.y = player_pos.y + (player_pos.x - out.x) * tan(angle_view);
	out.incrementation.y = CUBE_SIZE * tan(angle_view);
	return (out);
}

float	dda_checker(t_vec2f player_pos, float angle_view)
{
	t_dda	horizontal;
	t_dda	vertical;

	t_vec2f	new_h;
	t_vec2f	new_v;

	float	dist_h;
	float	dist_v;

	float	total_len;

	t_vec2	coord;

	coord.x = player_pos.x / CUBE_SIZE;
	coord.y = player_pos.y / CUBE_SIZE;

	total_len = 0;

	while (map[coord.x][coord.y] != 1)
	{
		horizontal = dda_horizontal(player_pos, angle_view);
		vertical = dda_vertical(player_pos, angle_view);

		new_h = add_vec2f(player_pos, horizontal.incrementation);
		new_v = add_vec2f(player_pos, vertical.incrementation);

		dist_h = dist(player_pos, new_h);
		dist_v = dist(player_pos, new_v);
		if (dist_h < dist_v)
		{
			player_pos = add_vec2f(player_pos, new_h);
			total_len += dist_h;
		}
		else
		{
			player_pos = add_vec2f(player_pos, new_v);
			total_len += dist_v;
		}
		coord.x = player_pos.x / CUBE_SIZE;
		coord.y = player_pos.y / CUBE_SIZE;
	}
	return (total_len);
}

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
