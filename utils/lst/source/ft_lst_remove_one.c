/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:34:37 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/06 14:56:04 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	lst_remove_one(t_list **root, void (*del)(void*))
{
	t_list	*new;

	if (!root || !(*root))
		return ;
	new = (*root)->next;
	lst_delone(*root, del);
	(*root) = new;
}
