/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:22:47 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/06 21:40:40 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vec2f	move_event(t_event event, int angle)
{
	float	cos;
	float	sin;

	cos = precompute(NULL).angle[angle].cos;
	sin = precompute(NULL).angle[angle].sin;
	if (event.keyboard.move_forward)
		return ((t_vec2f){-cos, -sin});
	if (event.keyboard.move_backward)
		return ((t_vec2f){+cos, +sin});
	if (event.keyboard.move_left)
		return ((t_vec2f){-sin, +cos});
	if (event.keyboard.move_right)
		return ((t_vec2f){+sin, -cos});
	return ((t_vec2f){0, 0});
}

bool	update_keyboard(t_screen *screen)
{
	t_data	*data;
	t_vec2f	move;

	data = screen->data;
	move = move_event(screen->mlx->event, data->player.view);
	move = vec2f_scale(vec2f_normalize(move), 0.03);
	move = vec2f_add(data->player.pos, move);
	if (data->map.data[(int)move.y][(int)move.x] == '0')
		data->player.pos = move;
	if (screen->mlx->event.keyboard.look_left)
		data->player.view -= data->player.mouse_speed;
	if (screen->mlx->event.keyboard.look_right)
		data->player.view += data->player.mouse_speed;
	data->player.view = y_wrap_angle(data->player.view);
	return (true);
}

bool	update_state(t_screen *screen)
{
	t_data	*data;

	data = screen->data;
	if (screen->mlx->event.keyboard.escape == true)
		return (mlx_loop_end(screen->mlx->mlx), false);
	if (screen->mlx->event.window.destroy == true)
		return (mlx_loop_end(screen->mlx->mlx), false);
	update_keyboard(screen);
	return (true);
}
