/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:22:41 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/02 13:56:04 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
# define VEC2_H

# include <math.h>
# include <stdbool.h>

typedef struct s_vec2 {
	int	x;
	int	y;
}	t_vec2;

t_vec2	vec2(int x, int y);

int		is_equal(t_vec2 a, t_vec2 b);
t_vec2	cmp_vec2(t_vec2 a, t_vec2 b);
t_vec2	substract_vec2(t_vec2 a, t_vec2 b);
t_vec2	add_vec2(t_vec2 a, t_vec2 b);
t_vec2	mul_vec2(t_vec2 a, t_vec2 b);
//t_vec2	generique(t_vec2 (*ft)(t_vec2, t_vec2), t_vec2 a, t_vec2 b);

bool	vec2i_in_range(t_vec2 v, t_vec2 min, t_vec2 max);

typedef struct s_vec2f {
	float	x;
	float	y;
}	t_vec2f;

t_vec2	vec2f_floor(t_vec2f v);
bool	vec2f_in_range(t_vec2f v, t_vec2f min, t_vec2f max);
t_vec2f	vec2f_add(t_vec2f a, t_vec2f b);
float	vec2f_dist(t_vec2f a, t_vec2f b);
t_vec2f	vec2f_normalize(t_vec2f v);
t_vec2f	vec2f_scale(t_vec2f v, float scale);
#endif
