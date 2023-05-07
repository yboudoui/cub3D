/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:47:04 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/05 17:34:53 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

# include "mlx.h"
# include <stdbool.h>

# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define ESCAPE 65307
# define ENTER 65293
# define CONTROL 65507
# define SHIFT 65505

/* typedef struct s_key { */
/* 	int		keycode; */
/* 	bool	pressed; */
/* }	t_key; */
/*
typedef enum e_keycode {
W_KEY = 119
S_KEY = 115
A_KEY = 97
D_KEY = 100
LEFT_ARROW = 65361
RIGHT_ARROW = 65363
UP_ARROW = 65362
DOWN_ARROW = 65364
ESCAPE = 65307
ENTER = 65293
CONTROL = 65507
SHIFT = 65505
}	t_keycode;
*/
typedef struct s_event_keyboard {
	bool	control_key;
	bool	escape;
	bool	enter;
	bool	move_forward;
	bool	move_backward;
	bool	move_left;
	bool	move_right;
	bool	look_up;
	bool	look_down;
	bool	look_left;
	bool	look_right;
}	t_event_keyboard;

void	keyboard_event_handlers(void *win, t_event_keyboard *event);
#endif
