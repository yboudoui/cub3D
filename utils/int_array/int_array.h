/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_array.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 06:10:02 by yboudoui          #+#    #+#             */
/*   Updated: 2022/11/20 17:18:26 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT_ARRAY_H
# define INT_ARRAY_H

# include <limits.h>
# include "memory.h"

typedef struct s_int_array	t_int_array;

struct s_int_array {
	size_t	len;
	int		*array;
};

t_int_array	*alloc_int_array(size_t len);
void		get_min_max(t_int_array array, int *min, int *max);
void		free_int_array(void *data);
#endif
