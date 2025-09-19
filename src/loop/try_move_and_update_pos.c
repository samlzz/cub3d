/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_move_and_update_pos.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:15:11 by eazard            #+#    #+#             */
/*   Updated: 2025/09/19 10:57:47 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

#include "loop.h"
#include "test/debug.h"

static void	_block_log_(int32_t x, int32_t y, char c, char *reason)
{
	if (UNTEXTURED_RAYCASTING_DEBUG)
	{
		fprintf(stderr, "(%i,%i) blocking mouvement\n", x, y);
		fprintf(stderr, "c = %c\n", c);
		fprintf(stderr, "reason : %s\n", reason);
		fflush(stderr);
	}
}

static bool	_is_blocking_(t_data *data, int32_t x, int32_t y)
{
	char	c;

	c = data->map.g.grid[y][x];
	if (x < 0 || y < 0)
		return (_block_log_(x, y, c, "< 0"), true);
	if (x >= data->map.g.dim.x
		|| y >= data->map.g.dim.y)
		return (_block_log_(x, y, c, "> dim"), true);
	if (c == '1' || c == '\n' || c == '\0' || c == ' ')
		return (_block_log_(x, y, c, "unwalkable char"), true);
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

void	try_move_and_update_pos(t_data *data, t_vec2d move_try)
{
	double	player_radius;
	double	try_x;
	double	try_y;

	player_radius = PLAYER_RADIUS;
	try_x = data->camera.pos.x + move_try.x;
	try_y = data->camera.pos.y;
	if (_can_stand_at_(data, try_x, try_y, player_radius))
		data->camera.pos.x = try_x;
	try_x = data->camera.pos.x;
	try_y = data->camera.pos.y + move_try.y;
	if (_can_stand_at_(data, try_x, try_y, player_radius))
		data->camera.pos.y = try_y;
}
