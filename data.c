/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:04:20 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/07 16:31:06 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_data	data_init(t_screen *screen, t_color c, t_color f, char **map)
{
	t_data	data;

	data.map = (t_map){map, (t_vec2){10, 12}, vec2(0)};
	data.texture[NORTH] = texture_init(screen->mlx, "./texture/north.xpm");
	data.texture[SOUHT] = texture_init(screen->mlx, "./texture/south.xpm");
	data.texture[EAST] = texture_init(screen->mlx, "./texture/east.xpm");
	data.texture[WEST] = texture_init(screen->mlx, "./texture/weast.xpm");
	data.floor_ceilling = image_env(screen, c, f);
	data.walls = ft_calloc(screen->size.x, sizeof(t_dda));
	return (data);
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

void	player_init(t_data *data, t_vec2f pos, float view)
{
	data->player.pos = pos;
	data->player.fov = 60.0;
	precompute_init(data->player.fov, WIDTH);
	data->player.hfov = c(60.0 / 2);
	data->player.view = c(view + 90);
	data->player.mouse_speed = c(1);
}
