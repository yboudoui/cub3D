/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:57:50 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/27 07:12:50 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "mlx.h"
# include <stdbool.h>

typedef struct s_event_window {
	bool	destroy;
}	t_event_window;

void	window_event_handlers(void *win, t_event_window *event);

#endif
