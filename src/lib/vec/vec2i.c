/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:35:24 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/20 11:28:26 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec2i	vec2i_sum(t_vec2i vec1, t_vec2i vec2)
{
	t_vec2i	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	return (result);
}

t_vec2i	vec2i_scalar_mult(t_vec2i vec, int32_t scalar)
{
	t_vec2i	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	return (result);
}
