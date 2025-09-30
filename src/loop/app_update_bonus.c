/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_update_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:09:09 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 18:05:54 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef CUB3D_BONUS

# include "data/camera.h"
# include "data/data.h"
# include "loop.h"
# include "vec/vec.h"
# include "door/door.h"

void	update_angle(t_camera *cam, t_inputs *io,
				double time_delta_beetwen_frame)
{
	double	delta;

	delta = ROT_SPEED * time_delta_beetwen_frame
		* (double )(io->turn_left - io->turn_right);
	delta += -io->cursor.dx_accum * MOUSE_SENSITIVITY;
	io->cursor.dx_accum = 0;
	camera_rotate(cam, delta);
}

void	app_update(t_data *data, double time_delta_beetwen_frame)
{
	t_vec2i		player_target;

	if (data->inputs.try_to_interact_with_door == true)
	{
		if (player_target_is_a_reachable_door(data, &player_target) == true)
			change_door_state(&data->map.doors[player_target.y] \
													[player_target.x]);
		data->inputs.try_to_interact_with_door = false;
	}
	update_position(data, time_delta_beetwen_frame);
	update_angle(&data->camera, &data->inputs, time_delta_beetwen_frame);
}

#endif
