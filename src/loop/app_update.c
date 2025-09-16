/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:09:09 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 16:30:07 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"
#include "test/test.h"

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
	t_vec2d	move_try;

	upfront_distance_delta = multiply_vec_by_scalar_2d(data->camera.dir,
			get_upfront_move_sclar(data, time_delta_beetwen_frame));
	side_distance_delta = multiply_vec_by_scalar_2d(data->camera.plane,
			get_side_move_sclar(data, time_delta_beetwen_frame));
	move_try = sum_vec_2d(upfront_distance_delta, side_distance_delta);
	clamp_move_try_length(&move_try, time_delta_beetwen_frame);
	try_move_and_update_pos(data, move_try);
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
	if (UNTEXTURED_RAYCASTING_DEBUG)
		camera_print(data->camera);
	return (0);
}
