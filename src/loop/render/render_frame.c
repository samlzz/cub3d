/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:37:25 by eazard            #+#    #+#             */
/*   Updated: 2025/09/18 15:57:04 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "vec/vec.h"
#include "data/camera.h"
#include "render.h"

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

	draw_clear(&data->mlx.img, C_SKY_BLUE, C_BROWN);
	dda.x = 0;
	while (dda.x < WIN_WIDTH)
	{
		dda.ray_dir = get_ray_dir(&data->camera, dda.x);
		dda_algorithm(data, &dda);
		dda.x++;
	}
}
