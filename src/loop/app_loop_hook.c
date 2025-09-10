/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_loop_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:07:14 by eazard            #+#    #+#             */
/*   Updated: 2025/09/10 11:15:54 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

static void	clamping_delta_beetwen_frame(double *time_delta_beetwen_frame)
{
	if (*time_delta_beetwen_frame < 0.0)
		*time_delta_beetwen_frame = 0.0;
	else if (*time_delta_beetwen_frame > 0.05)
		*time_delta_beetwen_frame = 0.05;
}

static void	set_time_delta_beetwen_frame(t_data *data,
		double *time_delta_beetwen_frame)
{
	data->camera.current_frame_time = get_time(T_SECOND);
	if (data->camera.last_frame_time)
		*time_delta_beetwen_frame = data->camera.current_frame_time
			- data->camera.last_frame_time;
	else
		*time_delta_beetwen_frame = 0.0;
	data->camera.last_frame_time = data->camera.current_frame_time;
}

int	app_loop_hook(t_data *data)
{
	double	time_delta_beetwen_frame;

	set_time_delta_beetwen_frame(data, &time_delta_beetwen_frame);
	clamping_delta_beetwen_frame(&time_delta_beetwen_frame);
	app_update(data, time_delta_beetwen_frame);
	// suite ...
	return (0);
}
