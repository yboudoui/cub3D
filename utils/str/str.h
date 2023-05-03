/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:18:51 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/03 17:14:04 by kdhrif           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include "memory.h"
# include <unistd.h>

int			ft_atoi(const char *nptr);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_is_nl_comma_fslash_dot(char c);
char		*ft_strdup(const char *s);
void		ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split(char	const *str, char c);
void		free_split(void *data);
#endif
