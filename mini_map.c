/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:41:24 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/06 19:28:52 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	precompute_minimap_grid(t_screen *screen)
{
	const t_vec2	block_size = {16, 16};
	const t_color	color = {.raw = 0xDDDDDD};
	t_data			*data;
	t_vec2			pos;

	data = screen->data;
	pos = (t_vec2){-1, -1};
	while (++pos.y < data->map.size.y)
	{
		pos.x = -1;
		while (++pos.x < data->map.size.x)
			image_put_empty_quad(data->mini_map,
				rectangle(vec2_mul(pos, block_size), block_size, color));
	}
}

void	init_minimap(t_screen *screen)
{
	const t_vec2	block_size = {16, 16};
	const t_color	color = {.raw = 0x0};
	t_data			*data;
	t_vec2			pos;

	data = screen->data;
	data->mini_map = image_new(screen->mlx,
			vec2_add(vec2_mul(data->map.size, vec2(16)), vec2(1)));
	image_clear(data->mini_map, (t_color){.raw = 0xFFFFFF});
	precompute_minimap_grid(screen);
	pos = (t_vec2){-1, -1};
	while (++pos.y < data->map.size.y)
	{
		pos.x = -1;
		while (++pos.x < data->map.size.x)
		{
			if (data->map.data[pos.y][pos.x] == '1')
				image_put_empty_quad(data->mini_map,
					rectangle(vec2_mul(pos, block_size), block_size, color));
		}
	}
}

void	draw_minimap(t_screen *screen)
{
	int		index;
	t_data	*data;
	t_pixel	new;
	t_pixel	pos;
	float	len;

	data = screen->data;
	image_put_to_image(data->mini_map, screen->img);
	index = 0;
	pos.color.raw = 0xFF0000;
	pos.coord = vec2_mul(vec2f_floor(data->player.pos), vec2(16));
	while (index < screen->size.x)
	{
		new.coord.x = pos.coord.x;
		new.coord.y = pos.coord.y;
		len = data->walls[index].len * 16.0;
		new.coord.x -= precompute(0).angle[data->walls[index].angle].cos * len;
		new.coord.y -= precompute(0).angle[data->walls[index].angle].sin * len;
		image_put_line(screen->img, pos, new);
		index += 1;
	}
}
