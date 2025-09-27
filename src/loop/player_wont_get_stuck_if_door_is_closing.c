/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_wont_get_stuck_if_door_is_closing.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:41:12 by eazard            #+#    #+#             */
/*   Updated: 2025/09/27 17:00:32 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"
#include "vec/vec.h"
#include "render/render.h"
#include <math.h>

/*
the case of the player pos is handle elsewhere, before this function
*/
static bool	_we_are_not_checking_at_player_pos(t_data *data,
				int32_t x, int32_t y)
{
	return (!((int)data->camera.pos.x == x
			&& (int)(row_from_worldY(data, data->camera.pos.y)) == y));
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
		|| (c == 'D' && _we_are_not_checking_at_player_pos(data, x, y)))
		return (true);
	return (false);
}

static bool	_door_closing_isnt_to_close_(t_data *data,
				double x, double y, double r)
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

static bool	we_are_about_to_open_a_door(t_data *data, t_vec2i *player_target)
{
	return (data->map.doors[player_target->y][player_target->x].state \
				== DOOR_CLOSED);
}

bool	player_wont_get_stuck_if_door_is_closing(
				t_data *data, t_vec2i *player_target)
{
	return (we_are_about_to_open_a_door(data, player_target)
		|| (_door_closing_isnt_to_close_(data, data->camera.pos.x, \
			data->camera.pos.y, PLAYER_RADIUS)));
}
