/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:47:02 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/21 11:00:21 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	lst_iter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

t_list	*lst_map(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*output;
	t_list	*tmp;

	output = NULL;
	while (lst)
	{
		tmp = lst_new(f(lst->content));
		if (NULL != tmp)
			lst_add_back(&output, tmp);
		else
			return (lst_clear(&output, del), output);
		lst = lst->next;
	}
	return (output);
}
