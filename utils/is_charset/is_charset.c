/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_charset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:50:19 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/03 13:42:51 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "is_charset.h"

bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool	ft_isspace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

bool	ft_notspace(int c)
{
	return (!ft_isspace(c));
}

void	ft_skip(char **str, t_pf_is_charset charset)
{
	while (**str && charset(**str))
		(*str)++;
}

bool	ft_skiped(char **str, t_pf_is_charset charset)
{
	bool	flag;

	flag = charset(**str);
	while (**str && (charset(**str) && flag))
		(*str)++;
	while (**str && (!charset(**str) && !flag))
		(*str)++;
	return (flag);
}
