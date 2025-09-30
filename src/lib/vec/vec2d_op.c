/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2d_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:34:46 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 14:20:19 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "vec.h"

t_vec2d	vec2d_sum(t_vec2d vec1, t_vec2d vec2)
{
	t_vec2d	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	return (result);
}

t_vec2d	vec2d_minus(t_vec2d vec1, t_vec2d vec2)
{
	t_vec2d	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	return (result);
}

t_vec2d	vec2d_scalar_mult(t_vec2d vec, double scalar)
{
	t_vec2d	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	return (result);
}
