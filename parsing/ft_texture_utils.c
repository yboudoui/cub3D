/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:59:23 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/03 16:59:28 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool check_texture_name(char const *line, char const *texture_name)
{
	int	i;

	i = 0;
	/* printf("line: %s\n", line); */
	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			i++;
			continue;
		}
		if (ft_strncmp(line + i, texture_name, ft_strlen(texture_name)) == 0)
			return (true);
		i++;
	}
	return (false);
}

char *get_texture_path(char const *line, char const *texture_name)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			i++;
			continue;
		}
		if (ft_strncmp(line + i, texture_name, ft_strlen(texture_name)) == 0)
		{
			i += ft_strlen(texture_name);
			while (line[i] && ft_isspace(line[i]))
				i++;
			return (ft_strdup(line + i));
		}
		i++;
	}
	return (NULL);
}
