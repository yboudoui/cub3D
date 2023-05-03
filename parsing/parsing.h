/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:00:22 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/02 18:04:22 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_config
{
	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;
	int floor_color;
	int ceiling_color;
	char **map;
}	t_config;
