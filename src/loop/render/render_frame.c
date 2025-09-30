/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:37:25 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 17:19:49 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "data/data.h"
#include "data/camera.h"
#include "vec/vec.h"
#include "render.h"
#include "minimap.h"

t_vec2d	get_ray_dir(t_camera *cam, int32_t x)
{
	double	camera_x;

	camera_x = 2.0 * (double)x / (WIN_WIDTH - 1) - 1.0;
	return (vec2d_sum(cam->dir,
			vec2d_scalar_mult(cam->plane, camera_x * cam->fov_factor)));
}

#ifdef CUB3D_BONUS

void	render_frame(t_data *data)
{
	t_dda_data	dda;

	draw_clear(&data->mlx.game,
		data->map.ceil_colr.value, data->map.floor_colr.value);
	dda.x = 0;
	while (dda.x < WIN_WIDTH)
	{
		dda.ray_dir = get_ray_dir(&data->camera, dda.x);
		dda_algorithm(data, &dda);
		dda.x++;
	}
	set_up_sprites_for_sort(&data->map.bank, &data->camera);
	sort_sprite(&data->map.bank);
	render_sprites_in_fov(data);
	render_minimap(&data->mlx, &data->map.g, &data->camera);
}

#else

void	render_frame(t_data *data)
{
	t_dda_data	dda;

	draw_clear(&data->mlx.game,
		data->map.ceil_colr.value, data->map.floor_colr.value);
	dda.x = 0;
	while (dda.x < WIN_WIDTH)
	{
		dda.ray_dir = get_ray_dir(&data->camera, dda.x);
		dda_algorithm(data, &dda);
		dda.x++;
	}
}

#endif
