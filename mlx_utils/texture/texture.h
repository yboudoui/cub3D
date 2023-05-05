/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 07:11:07 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/05 17:18:54 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "image.h"

typedef struct s_vec3f { //to move
	float	x;
	float	y;
	float	z;
}	t_vec3f;

typedef struct s_normal_map {
	t_vec3f	**map;
	t_vec2	size;
}	t_normal_map;

typedef struct s_texture {
	t_image			*img;
	t_normal_map	nmap;
}	t_texture;

t_normal_map	normal_map_create(t_mlx *mlx, char *img_path);
#endif
