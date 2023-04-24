/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 00:14:36 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/06 17:10:38 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

static int	ft_is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	while (ft_is_in_set(*s1, set))
		s1++;
	end = ft_strlen(s1) - 1;
	while (ft_is_in_set(s1[end], set))
		end--;
	if (!end)
		return (ft_substr(s1, 0, 1));
	return (ft_substr(s1, 0, end + 1));
}
