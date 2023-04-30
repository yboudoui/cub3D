/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:22:47 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/30 18:15:28 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
static bool	update_control(t_screen *screen)
{
	if (screen->mlx->event.mouse.scrol_up)
	if (screen->mlx->event.mouse.scrol_down)
	screen->mlx->event.mouse.scrol_up = false;
	screen->mlx->event.mouse.scrol_down = false;
	return (true);
}
*/

/*
static bool	update_scrol(t_screen *screen)
{
	if (screen->mlx->event.mouse.scrol_up)
	if (screen->mlx->event.mouse.scrol_down)
	if (screen->pad < 1.0f)
	screen->mlx->event.mouse.scrol_up = false;
	screen->mlx->event.mouse.scrol_down = false;
	return (true);
}
*/

float	wrap_angle(float angle_deg)
{
	float	angle_mod;

	angle_mod = fmod(angle_deg, 360.0);
	if (angle_mod < 0)
		angle_mod += 360.0;
	return (angle_mod);
}

bool	update_keyboard(t_screen *screen)
{
	t_data	*data;
	
	data = screen->data;
	if (screen->mlx->event.keyboard.move_forward)
	{
		data->player.pos.x += cosf(data->player.view * M_PI / 180.0) * data->player.mouse_speed;
		data->player.pos.y += sinf(data->player.view * M_PI / 180.0) * data->player.mouse_speed;
	}
	if (screen->mlx->event.keyboard.move_backward)
{
	data->player.pos.x -= cosf(data->player.view * M_PI / 180.0) * data->player.mouse_speed;
	data->player.pos.y -= sinf(data->player.view * M_PI / 180.0) * data->player.mouse_speed;
}

if (screen->mlx->event.keyboard.move_left)
{
	data->player.pos.x += sinf(data->player.view * M_PI / 180.0) * data->player.mouse_speed;
	data->player.pos.y -= cosf(data->player.view * M_PI / 180.0) * data->player.mouse_speed;
}

if (screen->mlx->event.keyboard.move_right)
{
	data->player.pos.x -= sinf(data->player.view * M_PI / 180.0) * data->player.mouse_speed;
	data->player.pos.y += cosf(data->player.view * M_PI / 180.0) * data->player.mouse_speed;
}

if (screen->mlx->event.keyboard.look_left)
{
	data->player.view -= data->player.mouse_speed;
}

if (screen->mlx->event.keyboard.look_right)
{
	data->player.view += data->player.mouse_speed;
}

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
