/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:36:53 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/06 14:38:31 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

int	lst_size(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_list	*lst_last(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
