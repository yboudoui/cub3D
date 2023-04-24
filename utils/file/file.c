/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:52:34 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/24 18:12:37 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

t_list	*read_file(char *path, int oflag, void *(*f)(char*), t_fp_del del)
{
	int		fd;
	char	*line;
	void	*tmp;
	t_list	*out;

	fd = open(path, oflag);
	if (fd < 0)
		return (NULL);
	out = NULL;
	while (true)
	{
		line = get_next_line(fd);
		if (NULL == line)
			break ;
		tmp = f(line);
		free(line);
		if (NULL == tmp || false == lst_create_back(&out, tmp))
		{
			close(fd);
			return (lst_clear(&out, del), NULL);
		}
	}
	return (close(fd), out);
}
