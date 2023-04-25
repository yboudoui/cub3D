/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:07:02 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/25 16:25:38 by yboudoui         ###   ########.fr       */
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
#include <stdio.h>
t_screen	*screen_create(char *path, int width, int height)
{
	t_screen	*out;

	out = ft_calloc(1, sizeof(t_screen));
	if (NULL == out)
		return (NULL);
	out->mlx = create_mlx(path, width, height);
	if (NULL == out->mlx)
		return (screen_destroy(out), NULL);
	out->img = image_new(out->mlx, width, height);
	out->center = (t_vec2){width / 2, height / 2};
	out->size = (t_vec2){width, height};
	return (out);
}
