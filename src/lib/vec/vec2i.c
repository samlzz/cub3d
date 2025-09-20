/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:35:24 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/20 22:02:10 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include "vec/ftmath_utils.h"

t_vec2i	vec2i_sum(t_vec2i vec1, t_vec2i vec2)
{
	t_vec2i	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	return (result);
}

t_vec2i	vec2i_minus(t_vec2i vec1, t_vec2i vec2)
{
	t_vec2i	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	return (result);
}

t_vec2i	vec2i_scalar_mult(t_vec2i vec, double scalar)
{
	t_vec2i	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	return (result);
}

t_vec2i	vec2i_clamp(t_vec2i vec, t_vec2i min, t_vec2i max)
{
	vec.x = ftm_clamp(vec.x, min.x, max.x);
	vec.y = ftm_clamp(vec.y, min.y, max.y);
	return (vec);
}