/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:15:46 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/04 13:56:48 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>
#include "lst.h"

void print_line(void *str)
{
	printf("%s\n", (char *)str);
}

void print_texture(t_config *config)
{
	if (config->north_texture)
		printf("north_texture: %s\n", config->north_texture);
	if (config->south_texture)
		printf("south_texture: %s\n", config->south_texture);
	if (config->west_texture)
		printf("west_texture: %s\n", config->west_texture);
	if (config->east_texture)
		printf("east_texture: %s\n", config->east_texture);
}

void print_colors(t_config *config)
{
	t_color color_ceiling;
	t_color color_floor;

	color_ceiling = config->ceiling_color;
	color_floor = config->floor_color;
	printf("Ceiling Color: R: %u, G: %u, B: %u, T: %u\n", color_ceiling.chanel[RED], color_ceiling.chanel[GREEN], color_ceiling.chanel[BLUE], color_ceiling.chanel[TRANSPARENCY]);
	printf("Floor Color: R: %u, G: %u, B: %u, T: %u\n", color_floor.chanel[RED], color_floor.chanel[GREEN], color_floor.chanel[BLUE], color_floor.chanel[TRANSPARENCY]);
}

void print_player(t_config *config)
{
	printf("Player Position: X: %f, Y: %f\n", config->player_pos.x, config->player_pos.y);
	printf("Player Angle: %f\n", config->player_angle);
}

void print_map(t_config *config)
{
	int i;

	i = 0;
	while (config->map[i])
	{
		printf("%s\n", config->map[i]);
		i++;
	}
}
