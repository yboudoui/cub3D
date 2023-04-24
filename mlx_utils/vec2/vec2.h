/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:22:41 by yboudoui          #+#    #+#             */
/*   Updated: 2023/04/24 19:54:18 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
# define VEC2_H

typedef struct s_vec2 {
	int	x;
	int	y;
}	t_vec2;

int		is_equal(t_vec2 a, t_vec2 b);
t_vec2	cmp_vec2(t_vec2 a, t_vec2 b);
t_vec2	substract_vec2(t_vec2 a, t_vec2 b);
t_vec2	add_vec2(t_vec2 a, t_vec2 b);
t_vec2	mul_vec2(t_vec2 a, t_vec2 b);
//t_vec2	generique(t_vec2 (*ft)(t_vec2, t_vec2), t_vec2 a, t_vec2 b);

typedef struct s_vec2f {
	float	x;
	float	y;
}	t_vec2f;

#endif
