/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:00:02 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/07 17:29:30 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (i + j + 1));
	if (!ptr)
		return (NULL);
	k = -1;
	while (++k < i)
		ptr[k] = s1[k];
	k = 0;
	while (k < j)
	{
		ptr[i + k] = s2[k];
		k++;
	}
	ptr[i + j] = '\0';
	return (ptr);
}
