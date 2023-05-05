/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:22:47 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/05 17:44:15 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	wrap_angle(float angle_deg)
{
	float	angle_mod;

	angle_mod = fmod(angle_deg, 360.0);
	if (angle_mod < 0)
		angle_mod += 360.0;
	return (angle_mod);
}

t_vec2f	move_event(t_event event, float angle)
{
	float	cos;
	float	sin;

	cos = cosf(angle * M_PI / 180.0);
	sin = sinf(angle * M_PI / 180.0);
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
	move = (t_vec2f){0, 0};
	move = move_event(screen->mlx->event, data->player.view);
	move = vec2f_scale(vec2f_normalize(move), 0.03);
	data->player.pos = vec2f_add(data->player.pos, move);
	if (screen->mlx->event.keyboard.look_left)
		data->player.view -= data->player.mouse_speed;
	if (screen->mlx->event.keyboard.look_right)
		data->player.view += data->player.mouse_speed;
	data->player.view = wrap_angle(data->player.view);
	return (true);
}

bool	update_state(t_screen *screen)
{
	t_data	*data;

	data = screen->data;
	if (screen->mlx->event.mouse.delta.x)
	{
		if (screen->mlx->event.mouse.delta.x > 0)
			data->player.view += 0.1 * data->player.mouse_speed;
		else
			data->player.view -= 0.1 * data->player.mouse_speed;
		screen->mlx->event.mouse.delta.x = 0;
		data->player.view = wrap_angle(data->player.view);
	}
	if (screen->mlx->event.keyboard.escape == true)
		return (mlx_loop_end(screen->mlx->mlx), false);
	if (screen->mlx->event.window.destroy == true)
		return (mlx_loop_end(screen->mlx->mlx), false);
	update_keyboard(screen);
	return (true);
}
