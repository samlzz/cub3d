/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:37:25 by eazard            #+#    #+#             */
/*   Updated: 2025/09/15 12:11:15 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// static void	test_draw_vline(t_data *data)
// {
// 	draw_vline(data, (t_line){WINDOW_WIDTH/2 - 50,            0,                WINDOW_HEIGHT}, RED); // rouge, pleine hauteur
// 	draw_vline(data, (t_line){WINDOW_WIDTH/2,50,               WINDOW_HEIGHT-50}, RED); // vert, centré, marges haut/bas
// 	draw_vline(data, (t_line){WINDOW_WIDTH/2 + 20,100,              300},            RED); // bleu, à droite, segment court
// 	draw_vline(data, (t_line){WINDOW_WIDTH/2 - 20,          0,                WINDOW_HEIGHT},              RED); // blanc, hauteur nulle (rien visible)
// }

static	t_vec2d	get_ray_dir(t_data *data, int x)
{
	double	camera_x;

	camera_x = 2.0 * (double)x / (WINDOW_WIDTH - 1) - 1.0;
	return (sum_vec_2d(data->camera.dir,
			multiply_vec_by_scalar_2d(data->camera.plane, camera_x
			* data->camera.fov_factor)));
}

void	render_frame(t_data *data)
{
	t_dda_data	dda;

	draw_clear(data, SKY_BLUE, DARK_GRAY);
	dda.x = 0;
	while (dda.x < WINDOW_WIDTH)
	{
		dda.ray_dir = get_ray_dir(data, dda.x);
		dda_algorithm(data, &dda);
		dda.x++;
	}
}
