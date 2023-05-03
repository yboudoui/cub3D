/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:50:54 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/03 12:15:40 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include "get_next_line.h"
# include "lst.h"
# include "str.h"

typedef void	(*t_fp_del)(void *);
t_list	*read_file(char *path, int oflag, void *(*f)(char*), t_fp_del del);
t_list	*read_file_2(int fd, bool (*f)(char*), t_fp_del del);

#endif
