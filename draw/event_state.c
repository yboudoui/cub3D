/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:22:47 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/01 14:45:34 by yboudoui         ###   ########.fr       */
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

t_vec2f	vec2f_normalize(t_vec2f v)
{
	float	dist;

	dist = vec2f_dist((t_vec2f){0,0}, v);
	return ((t_vec2f){
		.x = v.x / dist,
		.y = v.y / dist,
	});
}

t_vec2f	vec2f_scale(t_vec2f v, float scale)
{
	return ((t_vec2f){
		.x = v.x * scale,
		.y = v.y * scale,
	});
}

bool	update_keyboard(t_screen *screen)
{
	t_data	*data;
	bool	m;
	t_vec2f	move;

	move = (t_vec2f){0, 0};
	m = false;
	data = screen->data;
	if (screen->mlx->event.keyboard.move_forward)
	{
		move.x += cosf(data->player.view * M_PI / 180.0);// * data->player.mouse_speed;
		move.y += sinf(data->player.view * M_PI / 180.0);// * data->player.mouse_speed;
		m = true;
	}
	if (screen->mlx->event.keyboard.move_backward)
	{
		move.x -= cosf(data->player.view * M_PI / 180.0);// * data->player.mouse_speed;
		move.y -= sinf(data->player.view * M_PI / 180.0);// * data->player.mouse_speed;
		m = true;
	}
	if (screen->mlx->event.keyboard.move_left)
	{
		move.x += sinf(data->player.view * M_PI / 180.0);// * data->player.mouse_speed;
		move.y -= cosf(data->player.view * M_PI / 180.0);// * data->player.mouse_speed;
		m = true;
	}
	
	if (screen->mlx->event.keyboard.move_right)
	{
		move.x -= sinf(data->player.view * M_PI / 180.0);// * data->player.mouse_speed;
		move.y += cosf(data->player.view * M_PI / 180.0);// * data->player.mouse_speed;
		m = true;
	}
	if (m)
	{
		move = vec2f_normalize(move);
		move = vec2f_scale(move, 0.01);
		data->player.pos = vec2f_add(data->player.pos, move);
		m = false;
	}
	if (screen->mlx->event.keyboard.look_left)
		data->player.view -= data->player.mouse_speed;
	if (screen->mlx->event.keyboard.look_right)
		data->player.view += data->player.mouse_speed;
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
//		screen->mlx->event.mouse.delta.x = 0;
		data->player.view = wrap_angle(data->player.view);
	}

/*
	if (screen->mlx->event.keyboard.enter)
	{
		screen->mlx->event.keyboard.enter = false;
		return (true);
	}
*/
	

	if (screen->mlx->event.keyboard.escape == true)
		return (mlx_loop_end(screen->mlx->mlx), false);
	if (screen->mlx->event.window.destroy == true)
		return (mlx_loop_end(screen->mlx->mlx), false);
/*
	if (screen->mlx->event.keyboard.control_key)
		return (update_control(screen));
	else
		return (update_scrol(screen));
*/
	update_keyboard(screen);
	return (true);
}
