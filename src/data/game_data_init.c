/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_data_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:32:07 by eazard            #+#    #+#             */
/*   Updated: 2025/09/10 11:08:52 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

static void	game_camera_init(t_data *data)
{
	data->camera.dir.x = -1.0;
	data->camera.dir.y = 0.0;
	data->camera.plane.y = 1.0;
	data->camera.plane.x = 0.0;
	data->camera.pos.x = 0.0;
	data->camera.pos.y = 0.0;
	data->camera.fov_factor = 0.66;
}

void	game_data_init(t_data *data)
{
	game_camera_init(data);
}
