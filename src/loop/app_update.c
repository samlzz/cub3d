/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:09:09 by eazard            #+#    #+#             */
/*   Updated: 2025/09/10 15:24:21 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

double	get_side_move_sclar(t_data *data, double time_delta_beetwen_frame)
{
	return ((double)(data->inputs.right - data->inputs.left)
		* MOVE_SPEED * time_delta_beetwen_frame);
}

double	get_upfront_move_sclar(t_data *data, double time_delta_beetwen_frame)
{
	return ((double)(data->inputs.forward - data->inputs.backward)
			* MOVE_SPEED * time_delta_beetwen_frame);
}

static void	update_position(t_data *data, double time_delta_beetwen_frame)
{
	t_vec2d	upfront_distance_delta;
	t_vec2d	side_distance_delta;
	t_vec2d	new_pos;

	upfront_distance_delta = multiply_vec_by_scalar_2d(data->camera.dir,
			get_upfront_move_sclar(data, time_delta_beetwen_frame));
	side_distance_delta = multiply_vec_by_scalar_2d(data->camera.plane,
			get_side_move_sclar(data, time_delta_beetwen_frame));
	new_pos = sum_vec_2d(data->camera.pos,
			sum_vec_2d(upfront_distance_delta, side_distance_delta));
	data->camera.pos = new_pos;
}

static void	update_angle(t_data *data, double time_delta_beetwen_frame)
{
	double	angle_delta;

	angle_delta = ROT_SPEED * time_delta_beetwen_frame
		* (double )(data->inputs.turn_left - data->inputs.turn_right);
	camera_rotate(&data->camera, angle_delta);
}

int	app_update(t_data *data, double time_delta_beetwen_frame)
{

	update_position(data, time_delta_beetwen_frame);
	update_angle(data, time_delta_beetwen_frame);
	// if (UNTEXTURED_RAYCASTING_DEBUG)
	// 	camera_print(data->camera, "camera");
	return (0);
}
