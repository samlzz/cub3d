/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:13:59 by eazard            #+#    #+#             */
/*   Updated: 2025/09/18 15:49:02 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "loop/loop.h"
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

void	draw_wall_bend(t_data *data, t_dda_data *dda)
{
	int32_t		color;
	t_line		line;

	if (dda->side == 0)
	{
		if (dda->step.x < 0)
			color = EST_COLOR;
		else
			color = WEST_COLOR;
	}
	else if (dda->step.y < 0)
		color = NORTH_COLOR;
	else
		color = SOUTH_COLOR;
	line.column = dda->x;
	line.y0 = dda->draw_start;
	line.y1 = dda->draw_end;
	draw_vline(data, line, color);
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

void 	deduce_wall_x(t_data *data, t_dda_data *dda)
{
	if (dda->side == 0)
		dda->wall_x = data->camera.pos.y
		+ dda->perp_wall_dist * dda->ray_dir.y;
	else
		dda->wall_x = data->camera.pos.x
			+ dda->perp_wall_dist * dda->ray_dir.x;
	dda->wall_x -= floor(dda->wall_x);
}

void 	deduce_texture_related_data(t_data *data, t_dda_data *dda)
{
	dda->tex_img = &data->assets.cardinal_textures[dda->wall_orientation];
	dda->tex_x = (int)(dda->wall_x * (double)dda->tex_img->width);
	if ((dda->side == 0 && dda->ray_dir.x > 0)
		|| (dda->side == 1 && dda->ray_dir.y < 0))
		dda->tex_x = dda->tex_img->width - dda->tex_x - 1;
	dda->tex_step = (double)dda->tex_img->height
		/ dda->line_height;
	dda->tex_pos = (dda->draw_start - WINDOW_HEIGHT / 2 + dda->line_height / 2)
		* dda->tex_step;
	
}


void	dda_algorithm(t_data *data, t_dda_data *dda)
{
	init_dda(data, dda);
	dda_loop(data, dda);
	deduce_wall_orientation(dda);
	deduce_perp_wall_dist(data, dda);
	deduce_wall_band_size(data, dda);
	deduce_wall_x(data, dda);
	deduce_texture_related_data(data, dda);
	dda->y = dda->draw_start;
	while (dda->y < dda->draw_end)
	{
		dda->tex_y = (int)dda->tex_pos;
		if (dda->tex_y < 0)
			dda->tex_y  = 0;
		if (dda->tex_y > dda->tex_img->height - 1)
			dda->tex_y = dda->tex_img->height - 1;
		dda->tex_pos += dda -> tex_step;
		dda->color = *(uint32_t *)(dda->tex_img->data_addr + (dda->tex_img->line_len) * dda->tex_y + dda->tex_x * dda->tex_img->bpp / 8);
		if( dda->side == 1)
			dda->color = (dda->color >> 1) & 8355711;
		put_pixel_in_buffer(&data->mlx.img, dda->x, dda->y, dda->color);
		dda->y++;
	}
	// draw_wall_bend(data, dda);


	// data->camera.zbuf = dda->perp_wall_dist;
}
