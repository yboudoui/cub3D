/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:31:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/05 17:54:17 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include <stdbool.h>
# include "window.h"
# include "mouse.h"
# include "keyboard.h"

typedef struct s_event {
	t_event_keyboard	keyboard;
	t_event_mouse		mouse;
	t_event_window		window;
}	t_event;

void	event_handler(void *win, t_event *event);
#endif
