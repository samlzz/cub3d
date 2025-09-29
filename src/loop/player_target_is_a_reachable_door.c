/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_target_is_a_reachable_door.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:47:19 by eazard            #+#    #+#             */
/*   Updated: 2025/09/29 19:24:22 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"
#include "render/render.h"
#include "vec/ftmath_utils.h"

static bool	_cell_isnt_the_open_door_on_witch_we_stand(t_data *data,
				t_vec2i	*player_target)
{
	return (((int)data->camera.pos.x != player_target->x
			|| (int)(get_y_pos(data->map.g.dim.y, data->camera.pos.y))
		!= player_target->y));
}

static bool	_wall_or_door_has_been_hit(t_data *data,
				t_dda_data *dda, t_vec2i *player_target)
{
	char	cell;

	player_target->y = (int32_t)get_y_pos(data->map.g.dim.y, dda->map.y);
	if (player_target->y < 0 || player_target->y >= data->map.g.dim.y)
		return (true);
	player_target->x = (int32_t)dda->map.x;
	if (player_target->x < 0 || player_target->x >= data->map.g.dim.x)
		return (true);
	cell = data->map.g.grid[player_target->y][player_target->x];
	if (cell == 'D'
		&& _cell_isnt_the_open_door_on_witch_we_stand(data, player_target))
		return (true);
	if (cell == '1')
		return (true);
	return (false);
}

static void	_dda_loop_that_stop_at_any_door(t_data *data,
				t_dda_data *dda, t_vec2i *player_target)
{
	while (_wall_or_door_has_been_hit(data, dda, player_target) == false)
	{
		if (dda->side_dist.x < dda->side_dist.y)
		{
			dda->side_dist.x += dda->delta_dist.x;
			dda->map.x += dda->step.x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist.y += dda->delta_dist.y;
			dda->map.y += dda->step.y;
			dda->side = 1;
		}
	}
}

bool	player_target_is_a_reachable_door(t_data *data, t_vec2i *player_target)
{
	t_dda_data	dda;

	dda.x = WIN_WIDTH / 2;
	dda.ray_dir = get_ray_dir(&data->camera, dda.x);
	init_dda(data, &dda);
	_dda_loop_that_stop_at_any_door(data, &dda, player_target);
	if (data->map.g.grid[player_target->y][player_target->x] != 'D')
		return (false);
	deduce_perp_wall_dist(data, &dda);
	if (dda.perp_wall_dist < DOOR_DISTANCE_MAX_TO_BE_ABLE_TO_INTERACT
		&& player_wont_get_stuck_if_door_is_closing(
			data, player_target))
		return (true);
	else
		return (false);
}
