/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_camera_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:44:59 by eazard            #+#    #+#             */
/*   Updated: 2025/09/10 15:32:47 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

static void	set_up_camera_pos(t_data *data, size_t x, size_t y)
{
	if (UNTEXTURED_RAYCASTING_DEBUG)
		fprintf(stderr, "x = %lu, y = %lu\n", x, y);
	data->camera.pos.x = (double)x + 0.5;
	data->camera.pos.y = (double)y + 0.5;
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
	while (y < (size_t)data->map.dimensions.y)
	{
		x = 0;
		if (UNTEXTURED_RAYCASTING_DEBUG)
				fprintf(stderr, "%s\n", data->map.grid[y]);
		while (data->map.grid[y][x])
		{
			
			if (is_a_direction_character(data->map.grid[y][x]))
			{
				set_up_camera_pos(data, x, y);
				set_up_camera_dir_and_plane(data, data->map.grid[y][x]);
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
