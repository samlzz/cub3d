/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp_move_try_length.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:19:20 by eazard            #+#    #+#             */
/*   Updated: 2025/09/17 17:45:49 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"
#include "vec/ftmath_utils.h"

static inline double	_square_(double x)
{
	return (x * x);
}

/*
avoid the sqrt(2) boost when mooving in diag
*/
void	clamp_move_try_length(t_vec2d *move_try,
			double time_delta_beetwen_frame)
{
	double	unnormalized_norm;
	double	scalar_to_normalize;

	if (_square_(move_try->x) + _square_(move_try->y)
		> _square_(MOVE_SPEED * time_delta_beetwen_frame)) // optimised calcul : we dont have to calcul a sqrt in evry scenario
	{
		unnormalized_norm = vec2d_get_norm(*move_try); // sqrt calcul
		scalar_to_normalize = MOVE_SPEED * time_delta_beetwen_frame
			/ unnormalized_norm;
		*move_try = vec2d_scalar_mult(*move_try, scalar_to_normalize);
	}
}
