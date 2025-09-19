/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_loop_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:07:14 by eazard            #+#    #+#             */
/*   Updated: 2025/09/19 11:00:58 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test/debug.h"
#include "vec/ftmath_utils.h"
#include "mlx.h"
#include "./render/render.h"
#include "loop.h"
#include <stdio.h>

static void	set_time_delta_beetwen_frame(t_data *data,
		double *time_delta)
{
	data->camera.current_frame_time = get_time(T_SECOND);
	if (data->camera.last_frame_time)
		*time_delta = data->camera.current_frame_time
			- data->camera.last_frame_time;
	else
		*time_delta = 0.0;
	data->camera.last_frame_time = data->camera.current_frame_time;
}

int	app_loop_hook(t_data *data)
{
	double	beetwen_frame;

	set_time_delta_beetwen_frame(data, &beetwen_frame);
	beetwen_frame = ftm_clamp(beetwen_frame, 0.0, DELTA_T_CLAMP_MAX);
	if (LOOP_PRINT_DELTA_FRAME)
		dprintf(2, "Frame after %fsec\n", beetwen_frame);
	app_update(data, beetwen_frame);
	render_frame(data);
	mlx_put_image_to_window(data->mlx.display, data->mlx.window, data->mlx.img.image_ptr, 0, 0);
	return (0);
}
