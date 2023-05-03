/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:34:41 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/03 11:19:50 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mouse.h"

static int	mouse_press(int key, int x, int y, t_event_mouse *event)
{
	(void)x;
	(void)y;
	if (key == 4)
		event->scrol_up = true;
	if (key == 5)
		event->scrol_down = true;
	return (0);
}

static int	mouse_position(int x, int y, t_event_mouse *event)
{
	t_vec2	new;

	new = (t_vec2){x, y};
	if (x == event->pos.x && y == event->pos.y)
		event->delta = (t_vec2){0, 0};
	else
		event->delta = substract_vec2(new, event->pos);
	event->pos = new;
	return (0);
}

void	mouse_event_handlers(void *win, t_event_mouse *event)
{
	mlx_hook(win, 4, 1L << 2, mouse_press, event);
	mlx_hook(win, 6, 1L << 8, mouse_position, event);
}
