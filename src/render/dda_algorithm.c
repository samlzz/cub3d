/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:13:59 by eazard            #+#    #+#             */
/*   Updated: 2025/09/15 14:54:58 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
	dda->line_height = (int)(WINDOW_HEIGHT / dda->perp_wall_dist);
	dda->draw_start = WINDOW_HEIGHT / 2 - dda->line_height / 2;
	if (dda->draw_start < 0)
		dda->draw_start = 0;
	dda->draw_end = WINDOW_HEIGHT / 2 + dda->line_height / 2;
	if (dda->draw_end > WINDOW_HEIGHT - 1)
		dda->draw_end = WINDOW_HEIGHT - 1;
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
