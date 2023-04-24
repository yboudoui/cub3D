/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:53:12 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/24 14:20:40 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

inline void	image_put_line(t_image *img, t_pixel start, t_pixel end)
{
	t_bresenham_data	brd;

	brd = bresenham_data_init(start, end);
	while (1)
	{
		image_put_pixel(img, brd.current);
		if (1
			&& brd.current.coord.x == brd.end.coord.x
			&& brd.current.coord.y == brd.end.coord.y
		)
			break ;
		bresenham_data_update(&brd);
	}
}
