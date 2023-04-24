/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:14:30 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/24 17:08:53 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "screen.h"
# include "image.h"
# include <math.h>

void	draw_image(t_screen *data);
bool	update_state(t_screen *data);

#endif
