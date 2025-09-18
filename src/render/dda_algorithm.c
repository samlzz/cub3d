/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:13:59 by eazard            #+#    #+#             */
/*   Updated: 2025/09/18 12:10:22 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "loop/loop.h"
#include "render.h"

static void	_init_step_and_side_dist(t_data *data, t_dda_data *dda)
{
	if (dda->ray_dir.x < 0)
	{
		dda->step.x = -1.0;
		dda->side_dist.x = (data->camera.pos.x - dda->map.x)
			* dda->delta_dist.x;
	}
	else
	{
		dda->step.x = 1.0;
		dda->side_dist.x = (dda->map.x + 1.0 - data->camera.pos.x)
			* dda->delta_dist.x;
	}
	if (dda->ray_dir.y < 0)
	{
		dda->step.y = -1.0;
		dda->side_dist.y = (data->camera.pos.y - dda->map.y)
			* dda->delta_dist.y;
	}
	else
	{
		dda->step.y = 1.0;
		dda->side_dist.y = (dda->map.y + 1.0 - data->camera.pos.y)
			* dda->delta_dist.y;
	}
}

static void	_init_delta_dit(t_data *data, t_dda_data *dda)
{
	if (dda->ray_dir.x == 0)
	{
		if (dda->ray_dir.y == 0)
			clear_data(data, true, EC_DDA_RAYDIR_VEC_ZERO);
		dda->delta_dist.x = BIG;
	}
	else
		dda->delta_dist.x = fabs(1.0 / dda->ray_dir.x);
	if (dda->ray_dir.y == 0)
		dda->delta_dist.y = BIG;
	else
		dda->delta_dist.y = fabs(1.0 / dda->ray_dir.y);
}

void	init_dda(t_data *data, t_dda_data *dda)
{
	dda->map.x = floor(data->camera.pos.x);
	dda->map.y = floor(data->camera.pos.y);
	_init_delta_dit(data, dda);
	_init_step_and_side_dist(data, dda);
}

static bool	wall_has_been_hit(t_data *data, t_dda_data *dda) //TODO
{
	char	cell;
	t_vec2i	cubpos;

	cubpos.y = (int32_t)row_from_worldY(data, dda->map.y);
	if (cubpos.y < 0 || cubpos.y >= data->map.g.dim.y)
		return (true);
	cubpos.x = (int32_t)dda->map.x;
	if (cubpos.x < 0 || cubpos.x >= data->map.g.dim.x)
		return (true);
	cell = data->map.g.grid[cubpos.y][cubpos.x];
	if (cell == '1')
		return (true);
	return (false);
}

void	dda_loop(t_data *data, t_dda_data *dda)
{
	while (wall_has_been_hit(data, dda) == false)
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

void	calcul_perp_wall_dist(t_data *data, t_dda_data *dda)
{
	(void)data;
	if (dda->side == 0)
		dda->perp_wall_dist = (dda->map.x - data->camera.pos.x
				+ (1 - dda->step.x) / 2.0) / dda->ray_dir.x;
	else
		dda->perp_wall_dist = (dda->map.y - data->camera.pos.y
				+ (1 - dda->step.y) / 2.0) / dda->ray_dir.y;
}

void	calcul_wall_band_size(t_data *data, t_dda_data *dda)
{
	(void)data;
	dda->line_height = (int)(WIN_HEIGHT / dda->perp_wall_dist);
	dda->draw_start = WIN_HEIGHT / 2 - dda->line_height / 2;
	if (dda->draw_start < 0)
		dda->draw_start = 0;
	dda->draw_end = WIN_HEIGHT / 2 + dda->line_height / 2;
	if (dda->draw_end > WIN_HEIGHT - 1)
		dda->draw_end = WIN_HEIGHT - 1;
}

void	draw_wall_bend(t_data *data, t_dda_data *dda)
{
	int		color;
	t_line	line;

	if (dda->side == 0)
		color = 0xBBBBBB;
	else
		color = 0x888888;
	line.column = dda->x;
	line.y0 = dda->draw_start;
	line.y1 = dda->draw_end;
	draw_vline(data, line, color);
}

void	dda_algorithm(t_data *data, t_dda_data *dda)
{
	init_dda(data, dda);
	dda_loop(data, dda);
	calcul_perp_wall_dist(data, dda);
	calcul_wall_band_size(data, dda);
	draw_wall_bend(data, dda);
	data->camera.zbuf = dda->perp_wall_dist;
}
