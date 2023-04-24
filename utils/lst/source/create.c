/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 09:25:48 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/23 09:32:13 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

bool	lst_create_back(t_list **lst, void *content)
{
	t_list	*new;

	if (NULL == lst)
		return (false);
	new = lst_new(content);
	if (NULL == new)
		return (false);
	return (lst_add_back(lst, new));
}

bool	lst_create_front(t_list **lst, void *content)
{
	t_list	*new;

	if (NULL == lst)
		return (false);
	new = lst_new(content);
	if (NULL == new)
		return (false);
	return (lst_add_front(lst, new));
}
