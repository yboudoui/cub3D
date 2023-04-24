/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:46:04 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/27 07:10:12 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"

void	event_handler(void *win, t_event *event)
{
	mouse_event_handlers(win, &(event->mouse));
	keyboard_event_handlers(win, &(event->keyboard));
	window_event_handlers(win, &(event->window));
}
