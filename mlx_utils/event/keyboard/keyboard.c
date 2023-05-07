/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:46:37 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/03 11:19:21 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"
#include <stdio.h>

static int	key_press(int keycode, t_event_keyboard *event)
{
	if (keycode == 65293)
		event->enter = true;
	if (keycode == 65307)
		event->escape = true;
	if (keycode == W_KEY)
		event->move_forward = true;
	if (keycode == S_KEY)
		event->move_backward = true;
	if (keycode == A_KEY)
		event->move_left = true;
	if (keycode == D_KEY)
		event->move_right = true;
	if (keycode == UP_ARROW)
		event->look_up = true;
	if (keycode == DOWN_ARROW)
		event->look_down = true;
	if (keycode == LEFT_ARROW)
		event->look_left = true;
	if (keycode == RIGHT_ARROW)
		event->look_right = true;
	return (0);
}

static int	key_release(int keycode, t_event_keyboard *event)
{
	if (keycode == W_KEY)
		event->move_forward = false;
	if (keycode == S_KEY)
		event->move_backward = false;
	if (keycode == A_KEY)
		event->move_left = false;
	if (keycode == D_KEY)
		event->move_right = false;
	if (keycode == UP_ARROW)
		event->look_up = false;
	if (keycode == DOWN_ARROW)
		event->look_down = false;
	if (keycode == LEFT_ARROW)
		event->look_left = false;
	if (keycode == RIGHT_ARROW)
		event->look_right = false;
	if (keycode == 65507 || keycode == 65508)
		event->control_key = false;
	if (keycode == 65293)
		event->enter = false;
	if (keycode == 65307)
		event->escape = false;
	return (0);
}

void	keyboard_event_handlers(void *win, t_event_keyboard *event)
{
	mlx_hook(win, 2, 1L << 0, key_press, event);
	mlx_hook(win, 3, 1L << 1, key_release, event);
}
