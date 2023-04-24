/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:57:32 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/27 07:14:52 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static int	destroy_window(t_event_window *event)
{
	event->destroy = true;
	return (0);
}

void	window_event_handlers(void *win, t_event_window *event)
{
	mlx_hook(win, 17, 0L, destroy_window, event);
}
