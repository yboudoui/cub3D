/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:08:43 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/04 16:00:50 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

// Initialize the configuration structure with default values

bool parser(char *filename, t_config *config)
{
	int	fd;
	t_list *head;

	init_config(config);
	if (!ends_with(filename, ".cub"))
	{
		ft_error("Error\nInvalid file extension\n");
		return (false);
	}
	fd = open_file(filename);
	if (fd < 0)
	{
		ft_error("Error\nInvalid file\n");
		return (false);
	}
	head = read_file_2(fd, wrong_chars, free);
	if (!head)
		return (false);
	if (parse_texture(head, config) == false)
	{
		ft_error("Error\nInvalid texture\n");
		return (false);
	}
	if (parse_colors(head, config) == false)
	{
		ft_error("Error\nInvalid colors\n");
		return (false);
	}
	if (parse_map(head, config) == false)
	{
		ft_error("Error\nInvalid map\n");
		return (false);
	}
	/* print_colors(config); */
	/* print_texture(config); */
	/* lst_iter(head, print_line); */
	exit(0);
}
