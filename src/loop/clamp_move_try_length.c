/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalise_move_try.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:19:20 by eazard            #+#    #+#             */
/*   Updated: 2025/09/12 10:38:33 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

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

	if (_square_((*move_try).x) + _square_((*move_try).y)
		> _square_(MOVE_SPEED * time_delta_beetwen_frame)) // optimised calcul : we dont have to calcul a sqrt in evry scenario
	{
		unnormalized_norm = get_norm_vec_2d(*move_try); // sqrt calcul
		scalar_to_normalize = MOVE_SPEED * time_delta_beetwen_frame
			/ unnormalized_norm;
		*move_try = multiply_vec_by_scalar_2d(*move_try, scalar_to_normalize);
	}
}
