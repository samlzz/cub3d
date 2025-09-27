/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_target_is_a_reachable_door.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:47:19 by eazard            #+#    #+#             */
/*   Updated: 2025/09/27 16:25:00 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "loop.h"
#include "render/render.h"
#include <math.h>

static	t_vec2d	get_ray_dir(t_camera *cam, int32_t x)
{
	double	camera_x;

	camera_x = 2.0 * (double)x / (WIN_WIDTH - 1) - 1.0;
	return (vec2d_sum(cam->dir, 
		vec2d_scalar_mult(cam->plane, camera_x * cam->fov_factor)));
}

static bool	_wall_has_been_hit(t_data *data, t_dda_data *dda, t_vec2i *player_target)
{
	char	cell;

	player_target->y = (int32_t)row_from_worldY(data, dda->map.y);
	if (player_target->y < 0 || player_target->y >= data->map.g.dim.y)
		return (true);
	player_target->x = (int32_t)dda->map.x;
	if (player_target->x < 0 || player_target->x >= data->map.g.dim.x)
		return (true);
	cell = data->map.g.grid[player_target->y][player_target->x];
	if (cell == 'D'
		&& ((int)data->camera.pos.x != player_target->x
		|| (int)(row_from_worldY(data, data->camera.pos.y)) != player_target->y))
		return (true);
	if (cell == '1')
		return (true);
	return (false);
}

static void	_dda_loop_that_stop_at_any_door(t_data *data, t_dda_data *dda, t_vec2i *player_target)
{
	while (_wall_has_been_hit(data, dda, player_target) == false)
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
static bool	_is_blocking_(t_data *data, int32_t x, int32_t y)
{
	char	c;

	c = data->map.g.grid[y][x];
	if (x < 0 || y < 0)
		return (true);
	if (x >= data->map.g.dim.x
		|| y >= data->map.g.dim.y)
		return (true);
	if (c == '1' || c == '\n' || c == '\0' || c == ' '
		|| (c == 'D'
		&& ((int)data->camera.pos.x != x
		|| (int)(row_from_worldY(data, data->camera.pos.y)) != y)))
		return (true);
	return (false);
}

static bool	_can_stand_at_(t_data *data, double x, double y, double r)
{
	int32_t	minx;
	int32_t	maxx;
	int32_t	miny;
	int32_t	maxy;

	minx = (int32_t)floor(x - r - EPS);
	maxx = (int32_t)floor(x + r + EPS);
	miny = row_from_worldY(data, y + r + EPS);
	maxy = row_from_worldY(data, y - r - EPS);
	if (_is_blocking_(data, minx, miny)
		|| _is_blocking_(data, minx, maxy)
		|| _is_blocking_(data, maxx, miny)
		|| _is_blocking_(data, maxx, maxy))
		return (false);
	else
		return (true);
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
	if (!(dda.perp_wall_dist < DOOR_DISTANCE_MAX_TO_BE_ABLE_TO_INTERACT
		&& (data->map.doors[player_target->y][player_target->x].state == DOOR_CLOSED
		|| (_can_stand_at_(data, data->camera.pos.x, data->camera.pos.y, PLAYER_RADIUS)))))
		return (false);
	return (true);
}
