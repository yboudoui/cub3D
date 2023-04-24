/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:33:11 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/24 14:19:58 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# include "vec2.h"
# include "color.h"

typedef struct s_pixel {
	t_vec2	coord;
	t_color	color;
}	t_pixel;

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
