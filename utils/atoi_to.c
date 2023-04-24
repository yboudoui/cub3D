/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_to.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:00:50 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/23 08:49:13 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "is_charset.h"
#include <limits.h>

bool	ft_atoi_to(char **str, int *result)
{
	int				sign;
	long long int	out;

	ft_skip(str, ft_isspace);
	sign = (**str == '+') - (**str == '-');
	(*str) += (!!sign);
	if (!ft_isdigit(**str))
		return (false);
	if (!result)
		return (ft_skip(str, ft_isdigit), true);
	out = 0;
	while (ft_isdigit(**str))
		out = (out * 10) + (*(*str)++ - '0');
	out *= ((!!sign) * sign) + (!sign);
	if ((**str) || out < INT_MIN || out > INT_MAX)
		return (false);
	return (*result = out, true);
}
