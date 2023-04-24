/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:38:26 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/23 09:33:52 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

t_list	*lst_new(void *content)
{
	t_list	*output;

	output = malloc(sizeof(t_list));
	if (output)
		(*output) = (t_list){content, NULL};
	return (output);
}

bool	lst_add_front(t_list **lst, t_list *new)
{
	if (NULL == lst)
		return (false);
	new->next = *lst;
	*lst = new;
	return (true);
}

bool	lst_add_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst)
		return (false);
	tmp = *lst;
	if (tmp)
		lst_last(tmp)->next = new;
	else if (lst)
		(*lst) = new;
	return (true);
}
