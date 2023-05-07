/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:04:20 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/07 18:37:42 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

bool	data_init(t_screen *screen, t_config config)
{
	static t_data	data;

	data.map = (t_map){config.map, config.map_size};
	data.texture[NORTH] = texture_init(screen->mlx, config.north_texture);
	data.texture[SOUHT] = texture_init(screen->mlx, config.south_texture);
	data.texture[EAST] = texture_init(screen->mlx, config.east_texture);
	data.texture[WEST] = texture_init(screen->mlx, config.west_texture);
	data.floor_ceilling = image_env(screen,
			config.ceiling_color, config.floor_color);
	data.walls = ft_calloc(screen->size.x, sizeof(t_dda));
	if (1
		&& data.texture[NORTH] && data.texture[EAST]
		&& data.texture[SOUHT] && data.texture[WEST]
		&& data.floor_ceilling && data.walls)
		return (screen->data = &data, true);
	return (data_destroy(&data), false);
}

void	data_destroy(t_data *data)
{
	texture_destroy(data->texture[NORTH]);
	texture_destroy(data->texture[SOUHT]);
	texture_destroy(data->texture[WEST]);
	texture_destroy(data->texture[EAST]);
	delete_image(data->mini_map);
	delete_image(data->floor_ceilling);
	free(data->walls);
}

static int	c(float angle)
{
	return (angle / 360.0 * 7200);
}

bool	player_init(t_data *data, t_vec2f pos, float view)
{
	if (data == NULL)
		return (false);
	data->player.pos = pos;
	data->player.fov = 60.0;
	precompute_init(data->player.fov, WIDTH);
	data->player.hfov = c(60.0 / 2);
	data->player.view = c(view + 90);
	data->player.mouse_speed = c(1);
	return (true);
}
