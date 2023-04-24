/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:39:54 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/27 07:15:51 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOUSE_H
# define MOUSE_H

# include "vec2.h"
# include "mlx.h"
# include <stdbool.h>

typedef struct s_event_mouse {
	t_vec2	pos;
	bool	scrol_up;
	bool	scrol_down;
}	t_event_mouse;

void	mouse_event_handlers(void *win, t_event_mouse *event);

#endif
