/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:33:26 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/02 21:22:29 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "str.h"
#include <stdio.h>

int	ends_with_cub(const char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i < 4)
		return (-1);
	if (ft_strcmp(str + i - 4, ".cub"))
		return (-1);
	return (0);
}
