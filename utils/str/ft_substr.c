/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:54:47 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/06 17:10:40 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*output;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	len = ((str_len > len) * len)
		+ ((str_len < len) * str_len)
		+ ((str_len == len) * (len - start));
	len = (!(start > str_len) * len);
	output = ft_calloc(len + 1, sizeof(char));
	if (output)
		ft_memcpy(output, s + start, len);
	return (output);
}
