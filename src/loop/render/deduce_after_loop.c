/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deduce_after_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:20:29 by eazard            #+#    #+#             */
/*   Updated: 2025/09/19 17:18:31 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "render.h"

void	deduce_perp_wall_dist(t_data *data, t_dda_data *dda)
{
	(void)data;
	if (dda->side == 0)
		dda->perp_wall_dist = (dda->map.x - data->camera.pos.x
				+ (1 - dda->step.x) / 2.0) / dda->ray_dir.x;
	else
		dda->perp_wall_dist = (dda->map.y - data->camera.pos.y
				+ (1 - dda->step.y) / 2.0) / dda->ray_dir.y;
}

void	deduce_wall_band_size(t_data *data, t_dda_data *dda)
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

void	deduce_wall_orientation(t_dda_data *dda)
{
	if (dda->side == 0)
	{
		if (dda->step.x < 0)
			dda->wall_orientation = DIR_E;
		else
			dda->wall_orientation = DIR_W;
	}
	else if (dda->step.y < 0)
		dda->wall_orientation = DIR_N;
	else
		dda->wall_orientation = DIR_S;
}

void	deduce_wall_x(t_data *data, t_dda_data *dda)
{
	if (dda->side == 0)
		dda->wall_x = data->camera.pos.y
			+ dda->perp_wall_dist * dda->ray_dir.y;
	else
		dda->wall_x = data->camera.pos.x
			+ dda->perp_wall_dist * dda->ray_dir.x;
	dda->wall_x -= floor(dda->wall_x);
}

void	deduce_texture_related_data(t_data *data, t_dda_data *dda)
{
	dda->tex_img = &data->assets.cardinal_textures[dda->wall_orientation];
	dda->tex_x = (int)(dda->wall_x * (double)dda->tex_img->dim.x);
	if ((dda->side == 0 && dda->ray_dir.x > 0)
		|| (dda->side == 1 && dda->ray_dir.y < 0))
		dda->tex_x = dda->tex_img->dim.x - dda->tex_x - 1;
	dda->tex_step = (double)dda->tex_img->dim.y
		/ dda->line_height;
	dda->tex_pos = \
		(dda->draw_start - (float)WIN_HEIGHT / 2 + (float)dda->line_height / 2)
		* dda->tex_step;
}
