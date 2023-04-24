/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:58:26 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/23 09:32:14 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# include <stdbool.h>

typedef struct s_list{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*lst_new(void *content);

void	lst_clear(t_list **lst, void (*del)(void*));
void	lst_delone(t_list *lst, void (*del)(void*));
void	lst_remove_one(t_list **root, void (*del)(void*));

int		lst_size(t_list *lst);

t_list	*lst_map(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	lst_iter(t_list *lst, void (*f)(void *));

t_list	*lst_last(t_list *lst);

bool	lst_add_back(t_list **lst, t_list *new);
bool	lst_add_front(t_list **lst, t_list *new);

bool	lst_create_back(t_list **lst, void *content);

typedef bool	(*t_fp_iterator)(void**);
typedef void	(*t_fp_deletion)(void *);

typedef struct s_iterator {
	t_fp_iterator	iterator;
	t_fp_deletion	deletion;
}	t_iterator;

#endif
