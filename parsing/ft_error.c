/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:01:47 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/07 16:22:06 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	ft_error(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (false);
}

void	xfree(void *ptr)
{
	void	**addr;

	addr = ptr;
	if (addr == NULL)
		return ;
	free(*addr);
	*addr = NULL;
}
