/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply_vec_by_scalar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 09:17:47 by eazard            #+#    #+#             */
/*   Updated: 2025/09/10 09:20:45 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec2d	multiply_vec_by_scalar_2d(t_vec2d vec, double scalar)
{
	t_vec2d	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	return (result);
}

t_vec2i	multiply_vec_by_scalar_2i(t_vec2i vec, int32_t scalar)
{
	t_vec2i	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	return (result);
}
