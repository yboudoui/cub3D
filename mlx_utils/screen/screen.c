/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:07:02 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/27 16:06:12 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "screen.h"

void	screen_destroy(t_screen *screen)
{
	if (NULL == screen)
		return ;
	delete_image(screen->img);
	delete_mlx(screen->mlx);
	free(screen);
}

t_screen	*screen_create(char *path, t_vec2 size)
{
	t_screen	*out;

	out = ft_calloc(1, sizeof(t_screen));
	if (NULL == out)
		return (NULL);
	out->mlx = create_mlx(path, size.x, size.y);
	if (NULL == out->mlx)
		return (screen_destroy(out), NULL);
	out->img = image_new(out->mlx, size);
	out->center = (t_vec2){size.x / 2, size.y / 2};
	out->size = size;
	return (out);
}
