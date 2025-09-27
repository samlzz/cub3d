/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:09:09 by eazard            #+#    #+#             */
/*   Updated: 2025/09/27 15:54:31 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"
#include "test/test.h"
#include "vec/vec.h"
#include "door/door.h"
#include "render/render.h"

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

static void	update_angle(t_data *data, double time_delta_beetwen_frame)
{
	double	angle_delta;

	angle_delta = ROT_SPEED * time_delta_beetwen_frame
		* (double )(data->inputs.turn_left - data->inputs.turn_right);
	camera_rotate(&data->camera, angle_delta);
}

int	app_update(t_data *data, double time_delta_beetwen_frame)
{
	t_vec2i		player_target;
	t_vec2i		player_pos;
	
	if (data->inputs.try_to_interact_with_door == true)
	{
		player_pos.x = (int)data->camera.pos.x;
		player_pos.y = (int)row_from_worldY(data, data->camera.pos.y);
		if (player_target_is_a_reachable_door(data, &player_target) == true)
			change_door_state(&data->map.doors[player_target.y][player_target.x]);
		data->inputs.try_to_interact_with_door = false;
	}
	(void)player_pos;
	update_position(data, time_delta_beetwen_frame);
	update_angle(data, time_delta_beetwen_frame);
	if (UNTEXTURED_RAYCASTING_DEBUG)
		camera_print(data->camera);
	return (0);
}
