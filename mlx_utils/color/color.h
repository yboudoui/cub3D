/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 13:28:32 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/07 17:33:56 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef enum e_chanel_name {
	BLUE,
	GREEN,
	RED,
	TRANSPARENCY,
}	t_chanel_name;

typedef unsigned char	t_chanel;

typedef union u_color {
	unsigned char	chanel[4];
	unsigned int	raw;
}	t_color;

t_color	create_trgb(t_chanel t, t_chanel r, t_chanel g, t_chanel b);
t_color	color_create_raw(unsigned int raw);

void	color_brightness(t_color *c, float brightness);
void	color_contrast(t_color *c, float contrast);

t_color	interpolate_color(t_color a, float t, t_color b);

#endif
