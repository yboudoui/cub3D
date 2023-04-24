/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:52:01 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/14 14:52:05 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "memory.h"

int	ft_create_stach(t_stash **root)
{
	char	*buffer;

	buffer = malloc(BUFFER_SIZE * sizeof(char));
	(*root) = malloc(sizeof(t_stash));
	if (!(*root) || !(buffer))
	{
		free(buffer);
		free(*root);
		return (ERROR);
	}
	(**root) = (t_stash){.buffer = buffer};
	return (OK);
}

void	ft_delete(t_stash **root)
{
	t_stash	*out;
	t_stash	*old;

	if (!root || !(*root))
		return ;
	old = (*root);
	out = (*root)->next;
	free(old->buffer);
	old->buffer = NULL;
	free(old);
	old = NULL;
	(*root) = out;
}

void	ft_delete_book(t_book **root)
{
	t_book	*old;

	if (!root)
		return ;
	old = *root;
	if (old->next)
		old->next->prev = old->prev;
	if (old->prev)
		old->prev->next = old->next;
	ft_delete(&old->read);
	while (old->stash)
		ft_delete(&old->stash);
	free(old);
	(*root) = NULL;
}

void	ft_add_stash_to_book(t_book *book, t_stash *stash)
{
	book->len += stash->readed;
	if (!book->stash)
		book->stash = stash;
	else
		book->last->next = stash;
	book->last = stash;
}
