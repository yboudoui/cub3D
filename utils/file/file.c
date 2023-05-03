/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:52:34 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/03 13:55:26 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "parsing.h"
#include <stdio.h>

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

t_list	*read_file_2(int fd, bool (*f)(char*), t_fp_del del)
{
	char	*line;
	void	*tmp;
	t_list	*out;

	out = NULL;
	while (true)
	{
		line = get_next_line(fd);
		if (NULL == line)
			break ;
		if (f(line) == false)
		{
			ft_error("Error\nInvalid characters\n");
			free(line);
			lst_clear(&out, del);
			close(fd);
			return (NULL);
		}
		tmp = ft_strdup(line);
		free(line);
		if (NULL == tmp || false == lst_create_back(&out, tmp))
		{
			printf("Error on strdup or lst_create_back\n");
			close(fd);
			return (lst_clear(&out, del), NULL);
		}
	}
	return (close(fd), out);
}
