/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:45:53 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/27 07:13:12 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

t_mlx	*create_mlx(char *title, int width, int height)
{
	t_mlx	*out;

	out = ft_calloc(1, sizeof(t_mlx));
	if (NULL != out)
	{
		out->mlx = mlx_init();
		if (NULL == out->mlx)
			return (free(out), NULL);
		out->win = mlx_new_window(out->mlx, width, height, title);
		if (NULL == out->win)
			return (delete_mlx(out), NULL);
	}
	return (event_handler(out->win, &out->event), out);
}

void	delete_mlx(void *data)
{
	t_mlx	*input;

	if (NULL == data)
		return ;
	input = data;
	mlx_destroy_window(input->mlx, input->win);
	mlx_destroy_display(input->mlx);
	free(input->mlx);
	free(input);
}
