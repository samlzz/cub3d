/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_camera_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:44:59 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 16:36:59 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../data.h"
#include "test/test.h"

static void	set_up_camera_pos(t_data *data, size_t x, size_t y)
{
	if (UNTEXTURED_RAYCASTING_DEBUG)
		fprintf(stderr, "x = %lu, y = %lu\n", x, y);
	data->camera.pos.x = (double)x + 0.5;
	data->camera.pos.y = (double)(data->map.g.dim.y - (y  + 1)) + 0.5; // dimension va de 1 a dim.y. , y va de 0 a dim.y -1 , donc je fais + 1 dans le calcule
	if (UNTEXTURED_RAYCASTING_DEBUG)
		fprintf(stderr, "camera.pos.x = %f, camera.pos.y = %f\n",
			data->camera.pos.x, data->camera.pos.y);
}

static bool	is_a_direction_character(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static void	deduce_cam_setting_from_player_pos(t_data *data)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < (size_t)data->map.g.dim.y)
	{
		x = 0;
		if (UNTEXTURED_RAYCASTING_DEBUG)
				fprintf(stderr, "%s\n", data->map.g.grid[y]);
		while (data->map.g.grid[y][x])
		{
			
			if (is_a_direction_character(data->map.g.grid[y][x]))
			{
				set_up_camera_pos(data, x, y);
				set_up_camera_dir_and_plane(data, data->map.g.grid[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	game_camera_init(t_data *data)
{
	deduce_cam_setting_from_player_pos(data);
	data->camera.fov_factor = FOV_FACTOR;
}
