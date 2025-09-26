/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:37:25 by eazard            #+#    #+#             */
/*   Updated: 2025/09/25 17:51:42 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "data/data.h"
#include "data/camera.h"
#include "vec/vec.h"
#include "render.h"
#include "minimap.h"

static	t_vec2d	get_ray_dir(t_camera *cam, int32_t x)
{
	double	camera_x;

	camera_x = 2.0 * (double)x / (WIN_WIDTH - 1) - 1.0;
	return (vec2d_sum(cam->dir, 
		vec2d_scalar_mult(cam->plane, camera_x * cam->fov_factor)));
}

void	render_frame(t_data *data)
{
	t_dda_data	dda;

	render_minimap(&data->mlx.minimap, &data->map.g, &data->camera);
	draw_clear(&data->mlx.game, C_SKY_BLUE, C_BROWN);
	dda.x = 0;
	while (dda.x < WIN_WIDTH)
	{
		dda.ray_dir = get_ray_dir(&data->camera, dda.x);
		dda_algorithm(data, &dda);
		dda.x++;
	}
}
