/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_move_and_update_pos.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:15:11 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 14:50:20 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "cubmap.h"
#include "data/camera.h"
#include "loop.h"
#include "door/door.h"
#include "vec/ftmath_utils.h"

static bool	_is_blocking_(t_grid *map, t_door **doors, int32_t x, int32_t y)
{
	char	c;

	if (x < 0 || y < 0 || x >= map->dim.x || y >= map->dim.y)
		return (true);
	c = map->grid[y][x];
	return (c == '1'
		|| c == '\n'
		|| c == '\0'
		|| c == ' '
		|| (c == 'D' && doors[y][x].state == DOOR_CLOSED));
	return (false);
}

static bool	_can_stand_at_(t_map *map, double x, double y, double r)
{
	int32_t	minx;
	int32_t	maxx;
	int32_t	miny;
	int32_t	maxy;

	minx = (int32_t)floor(x - r - EPS);
	maxx = (int32_t)floor(x + r + EPS);
	miny = get_y_pos(map->g.dim.y, y + r + EPS);
	maxy = get_y_pos(map->g.dim.y, y - r - EPS);
	if (_is_blocking_(&map->g, map->doors, minx, miny)
		|| _is_blocking_(&map->g, map->doors, minx, maxy)
		|| _is_blocking_(&map->g, map->doors, maxx, miny)
		|| _is_blocking_(&map->g, map->doors, maxx, maxy))
		return (false);
	else
		return (true);
}

void	try_move_and_update_pos(t_data *data, t_vec2d move_try)
{
	double	player_radius;
	double	try_x;
	double	try_y;

	player_radius = PLAYER_RADIUS;
	try_x = data->camera.pos.x + move_try.x;
	try_y = data->camera.pos.y;
	if (_can_stand_at_(&data->map, try_x, try_y, player_radius))
		data->camera.pos.x = try_x;
	try_x = data->camera.pos.x;
	try_y = data->camera.pos.y + move_try.y;
	if (_can_stand_at_(&data->map, try_x, try_y, player_radius))
		data->camera.pos.y = try_y;
}
