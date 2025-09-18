/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:53:43 by eazard            #+#    #+#             */
/*   Updated: 2025/09/18 10:40:54 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	_init_step_and_side_dist(t_data *data, t_dda_data *dda)
{
	if (dda->ray_dir.x < 0)
	{
		dda->step.x = -1.0;
		dda->side_dist.x = (data->camera.pos.x - dda->map.x)
			* dda->delta_dist.x;
	}
	else
	{
		dda->step.x = 1.0;
		dda->side_dist.x = (dda->map.x + 1.0 - data->camera.pos.x)
			* dda->delta_dist.x;
	}
	if (dda->ray_dir.y < 0)
	{
		dda->step.y = -1.0;
		dda->side_dist.y = (data->camera.pos.y - dda->map.y)
			* dda->delta_dist.y;
	}
	else
	{
		dda->step.y = 1.0;
		dda->side_dist.y = (dda->map.y + 1.0 - data->camera.pos.y)
			* dda->delta_dist.y;
	}
}

static void	_init_delta_dit(t_data *data, t_dda_data *dda)
{
	if (dda->ray_dir.x == 0)
	{
		if (dda->ray_dir.y == 0)
			clear_data(data, true, DDA_RAYDIR_VEC_ZERO);
		dda->delta_dist.x = BIG;
	}
	else
		dda->delta_dist.x = fabs(1.0 / dda->ray_dir.x);
	if (dda->ray_dir.y == 0)
		dda->delta_dist.y = BIG;
	else
		dda->delta_dist.y = fabs(1.0 / dda->ray_dir.y);
}

void	init_dda(t_data *data, t_dda_data *dda)
{
	dda->map.x = floor(data->camera.pos.x);
	dda->map.y = floor(data->camera.pos.y);
	_init_delta_dit(data, dda);
	_init_step_and_side_dist(data, dda);
}
