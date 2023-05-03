/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:08:43 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/02 18:09:17 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

// Initialize the configuration structure with default values
t_config init_config()
{
	t_config config;

	config.north_texture = NULL;
	config.south_texture = NULL;
	config.west_texture = NULL;
	config.east_texture = NULL;
	config.floor_color = -1;
	config.ceiling_color = -1;
	config.map = NULL;

	return config;
}
