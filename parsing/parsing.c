/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:32:26 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/02 21:15:09 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "get_next_line.h"
#include "lst.h"

int	parsing(char *file)
{
	int	fd;
	t_list lst;
	int char_read;

	if (ends_with_cub(file) == -1)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	lst.content = get_next_line(fd);
	while (lst.content != NULL)
	{
		char_read = parse_config();
	}
	return (0);
}
