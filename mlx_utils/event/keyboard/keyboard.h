/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:47:04 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/27 07:15:30 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

# include "mlx.h"
# include <stdbool.h>

typedef struct s_event_keyboard {
	bool	control_key;
	bool	escape;
	bool	enter;
}	t_event_keyboard;

void	keyboard_event_handlers(void *win, t_event_keyboard *event);
#endif
