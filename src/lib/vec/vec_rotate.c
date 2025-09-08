/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:41:35 by eazard            #+#    #+#             */
/*   Updated: 2025/09/04 18:52:46 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/*
a positiv value for angle means a rotation on the left
a negativ value for angle means a rotation on the right
*/
void	vec_rotate(t_vec2d *vec, double angle)
{
	t_vec2d	rotated_vec;

	rotated_vec.x = vec->x * cos(angle) - vec->y * sin(angle);
	rotated_vec.y = vec->x * sin(angle) + vec->y * cos(angle);
	*vec = rotated_vec;
}

void	vec_left_rotate(t_vec2d *vec, double angle)
{
	vec_rotate(vec, angle);
}

void	vec_right_rotate(t_vec2d *vec, double angle)
{
	vec_rotate(vec, -angle);
}
