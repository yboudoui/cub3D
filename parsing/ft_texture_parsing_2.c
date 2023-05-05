/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture_parsing_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:18:14 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/05 15:20:08 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_unknown_properties(t_list *head)
{
	t_list	*tmp;
	char	*str;
	int		i;

	tmp = head;
	while (tmp)
	{
		i = 0;
		str = (char *)tmp->content;
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '0' || str[i] == '1')
			return (true);
		if (ft_isalnum(str[i]))
		{
			if (valid_texture_name(str) == false)
				return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	parse_texture(t_list *head, t_config *config)
{
	if (parse_texture_north(head, config) == false)
		return (false);
	if (parse_texture_south(head, config) == false)
		return (false);
	if (parse_texture_west(head, config) == false)
		return (false);
	if (parse_texture_east(head, config) == false)
		return (false);
	if (parse_unknown_properties(head) == false)
		return (false);
	return (true);
}
