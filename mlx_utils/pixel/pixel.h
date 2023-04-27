/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:00:30 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/27 15:19:05 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXEL_H
# define PIXEL_H

# include "vec2.h"
# include "color.h"

typedef struct s_pixel {
	t_vec2	coord;
	t_color	color;
}	t_pixel;

t_pixel	pixel(t_vec2 coord, t_color color);

#endif
