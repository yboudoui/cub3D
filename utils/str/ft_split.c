/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 08:46:09 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/14 17:40:24 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

static size_t	ft_is_word(const char **str, char c)
{
	size_t	flag;
	size_t	len;

	len = 0;
	flag = (c != (*str)[len]);
	while ((*str)[len] && (c != (*str)[len]) && flag)
		len += 1;
	while ((*str)[len] && (c == (*str)[len]) && !flag)
		len += 1;
	*str += len;
	return (len * flag);
}

char	**ft_split(char	const *str, char c)
{
	char		**out;
	size_t		len;
	size_t		words;
	char const	*tmp;
	size_t		index;

	tmp = str;
	words = -(!tmp);
	index = 0;
	while (tmp && *tmp)
		words += (!!ft_is_word(&tmp, c));
	out = ft_calloc(words + 1, sizeof(char *));
	while (out && *str && index <= words)
	{
		tmp = str;
		len = ft_is_word(&str, c);
		if (len)
		{
			out[index] = ft_substr(tmp, 0, len);
			index += 1;
		}
	}
	return (out);
}

void	free_split(void *data)
{
	char	**input;
	size_t	index;

	if (NULL == data)
		return ;
	input = data;
	index = 0;
	while (input[index])
	{
		free(input[index]);
		index++;
	}
	free(input);
}
