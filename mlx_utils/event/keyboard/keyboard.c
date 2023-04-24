/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:46:37 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/27 07:15:15 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static int	key_press(int keycode, t_event_keyboard *event)
{
	if (keycode == 65507 || keycode == 65508)
		event->control_key = true;
	if (keycode == 65293)
		event->enter = true;
	if (keycode == 65307)
		event->escape = true;
	return (0);
}

static int	key_release(int keycode, t_event_keyboard *event)
{
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
