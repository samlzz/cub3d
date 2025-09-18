/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:09:09 by eazard            #+#    #+#             */
/*   Updated: 2025/09/18 19:36:08 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data/camera.h"
#include "data/data.h"
#include "loop.h"
#include "test/test.h"
#include "vec/vec.h"

static inline double	get_side_move_sclar(t_data *data, double time_delta_beetwen_frame)
{
	return ((double)(data->inputs.right - data->inputs.left)
		* MOVE_SPEED * time_delta_beetwen_frame);
}

static inline double	get_upfront_move_sclar(t_data *data, double time_delta_beetwen_frame)
{
	return ((double)(data->inputs.forward - data->inputs.backward)
			* MOVE_SPEED * time_delta_beetwen_frame);
}

static void	update_position(t_data *data, double time_delta_beetwen_frame)
{
	t_vec2d	upfront_distance_delta;
	t_vec2d	side_distance_delta;
	t_vec2d	move_try;

	upfront_distance_delta = vec2d_scalar_mult(data->camera.dir,
			get_upfront_move_sclar(data, time_delta_beetwen_frame));
	side_distance_delta = vec2d_scalar_mult(data->camera.plane,
			get_side_move_sclar(data, time_delta_beetwen_frame));
	move_try = vec2d_sum(upfront_distance_delta, side_distance_delta);
	clamp_move_try_length(&move_try, time_delta_beetwen_frame);
	try_move_and_update_pos(data, move_try);
}

static void	update_angle(t_camera *cam, t_inputs *io, double time_delta_beetwen_frame)
{
	double	delta;

	delta = ROT_SPEED * time_delta_beetwen_frame
		* (double )(io->turn_left - io->turn_right);
	delta += - io->cursor.dx_accum * MOUSE_SENSITIVITY;
	io->cursor.dx_accum = 0;
	camera_rotate(cam, delta);
}

int	app_update(t_data *data, double time_delta_beetwen_frame)
{
	update_position(data, time_delta_beetwen_frame);
	update_angle(&data->camera, &data->inputs, time_delta_beetwen_frame);
	if (UNTEXTURED_RAYCASTING_DEBUG)
		camera_print(data->camera);
	return (0);
}
