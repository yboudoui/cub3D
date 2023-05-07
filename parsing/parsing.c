/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:08:43 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/07 15:55:24 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

// Initialize the configuration structure with default values
bool	parser(char *filename, t_config *config)
{
	int			fd;
	t_list		*head;

	init_config(config);
	if (!ends_with(filename, ".cub"))
		return (ft_error("Error\nInvalid file extension\n"));
	fd = open_file(filename);
	if (fd < 0)
		return (ft_error("Error\nInvalid file\n"));
	head = read_file_2(fd, wrong_chars, free);
	if (!head)
		return (ft_error("Error\nInvalid file\n"));
	if (parse_texture(head, config) == false)
		return (lst_clear(&head, free), ft_error("Error\nInvalid texture\n"));
	if (parse_colors(head, config) == false)
		return (lst_clear(&head, free), ft_error("Error\nInvalid colors\n"));
	if (parse_map(head, config) == false)
		return (lst_clear(&head, free), ft_error("Error\nInvalid map\n"));
	debug(config);
	return (lst_clear(&head, free), true);
}
