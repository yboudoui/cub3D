/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:00:50 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/24 17:09:03 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "memory.h"
# include "event.h"
# include "mlx.h"

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	t_event	event;
}	t_mlx;

t_mlx	*create_mlx(char *title, int width, int height);
void	delete_mlx(void *data);
#endif
