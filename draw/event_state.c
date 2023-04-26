/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:22:47 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/26 18:00:17 by yboudoui         ###   ########.fr       */
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
		if (data->player.view >= 180)
			data->player.view *= -1;
//		if (data->player.view < 0)
//			data->player.view = 180;
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
	return (true);
}