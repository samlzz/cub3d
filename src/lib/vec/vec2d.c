/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:34:46 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 14:20:23 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>

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

t_vec2i	vec2d_round(t_vec2d vec, bool round_greater)
{
	t_vec2i	rounded;

	if (round_greater)
	{
		rounded.x = round(vec.x);
		rounded.y = round(vec.y);
	}
	else
	{
		rounded.x = floor(vec.x);
		rounded.y = floor(vec.y);
	}
	return (rounded);
}

inline double	vec2d_get_norm(t_vec2d vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}
