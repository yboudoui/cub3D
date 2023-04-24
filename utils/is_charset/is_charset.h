/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_charset.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 22:30:04 by yboudoui          #+#    #+#             */
/*   Updated: 2022/08/22 15:06:09 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_CHARSET_H
# define IS_CHARSET_H

# include <stdbool.h>

typedef bool	(*t_pf_is_charset)(int);

bool	ft_isdigit(int c);
bool	ft_isspace(int c);
bool	ft_notspace(int c);
bool	ft_skiped(char **str, t_pf_is_charset charset);
void	ft_skip(char **str, t_pf_is_charset charset);

bool	ft_atoi_to(char **str, int *result);
#endif
