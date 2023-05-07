/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:28:55 by yboudoui          #+#    #+#             */
/*   Updated: 2023/05/05 18:39:44 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"

t_vec2	vec2_sub(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){
		.x = a.x - b.x,
		.y = a.y - b.y,
	});
}

t_vec2	vec2_mul(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){
		.x = a.x * b.x,
		.y = a.y * b.y,
	});
}

t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){
		.x = a.x + b.x,
		.y = a.y + b.y,
	});
}
