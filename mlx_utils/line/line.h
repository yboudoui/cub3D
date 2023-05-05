/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:33:11 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/05 07:03:08 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# include "pixel.h"

typedef struct s_line {
	t_pixel	start;
	t_pixel	end;
}	t_line;

typedef struct s_bresenham_data {
	t_vec2	derivative;
	t_vec2	slop;
	int		error;
	int		difference;
	t_pixel	start;
	t_pixel	end;
	t_pixel	current;
	struct s_color_interpolation {
		float	pad;
		float	current;
	}	color_interpolation;
}	t_bresenham_data;

t_bresenham_data	bresenham_data_init(t_pixel start, t_pixel end);
void				bresenham_data_update(t_bresenham_data *in);

#endif
