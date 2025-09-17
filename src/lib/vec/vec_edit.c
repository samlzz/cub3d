/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:09:59 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/17 17:17:42 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "vec.h"

/*
a positiv value for angle means a rotation on the left
a negativ value for angle means a rotation on the right
*/
void	vec2d_rotate(t_vec2d *vec, double angle)
{
	t_vec2d	rotated_vec;

	rotated_vec.x = vec->x * cos(angle) - vec->y * sin(angle);
	rotated_vec.y = vec->x * sin(angle) + vec->y * cos(angle);
	*vec = rotated_vec;
}

t_vec2d	vec2d_sum(t_vec2d vec1, t_vec2d vec2)
{
	t_vec2d	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	return (result);
}

t_vec2i	vec2i_sum(t_vec2i vec1, t_vec2i vec2)
{
	t_vec2i	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	return (result);
}

t_vec2d	vec2d_scalar_mult(t_vec2d vec, double scalar)
{
	t_vec2d	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	return (result);
}

t_vec2i	vec2i_scalar_mult(t_vec2i vec, int32_t scalar)
{
	t_vec2i	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	return (result);
}
