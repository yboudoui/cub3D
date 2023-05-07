/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdhrif <kdhrif@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:54:26 by kdhrif            #+#    #+#             */
/*   Updated: 2023/05/07 15:52:15 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*parse_submap(t_list *head, int i, char *str)
{
	t_list	*tmp;
	t_list	*out;
	t_list	*prev;

	tmp = head;
	out = NULL;
	while (tmp)
	{
		str = tmp->content;
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] && (str[i] == '1' || str[i] == '0'))
			break ;
		prev = tmp;
		tmp = tmp->next;
	}
	tmp = prev;
	while (tmp)
	{
		lst_add_back(&out, lst_new(ft_strdup(tmp->content)));
		tmp = tmp->next;
	}
	if (!out)
		return (NULL);
	return (out);
}

int	get_longest_line(t_list *tmp)
{
	int	max;
	int	len;

	max = 0;
	while (tmp)
	{
		len = ft_strlen((char *)tmp->content);
		if (len > max)
			max = len;
		tmp = tmp->next;
	}
	return (max);
}

void	map_str_transform(void *tmp)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)tmp;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			str[i] = '1';
		i++;
	}
	return ;
}

bool	zero_or_player(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

t_list	*get_equal_lines(t_list *tmp, int max)
{
	t_list	*new;
	char	*str;
	char	*tmp_str;
	int		i;

	new = NULL;
	while (tmp)
	{
		str = ft_strdup((char *)tmp->content);
		i = ft_strlen(str);
		while (i < max)
		{
			tmp_str = str;
			str = ft_strjoin(str, "1");
			free(tmp_str);
			if (!str)
				return (NULL);
			i++;
		}
		lst_add_back(&new, lst_new(str));
		tmp = tmp->next;
	}
	return (new);
}
