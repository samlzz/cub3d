/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_camera_dir_and_plane.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:48:20 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 16:17:15 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../data.h"

/*
 Facing North: dir = (0, -1), plane = (1, 0)
*/
static void	set_up_dir_and_plane_for_north(t_data *data)
{
    data->camera.dir.x   = 0.0;
    data->camera.dir.y   = 1.0;
    data->camera.plane.x = 1.0;
    data->camera.plane.y = 0.0;
}

/*
 Facing South: dir = (0, 1), plane = (-1, 0)
*/
static void	set_up_dir_and_plane_for_south(t_data *data)
{
    data->camera.dir.x   = 0.0;
    data->camera.dir.y   = -1.0;
    data->camera.plane.x = -1.0;
    data->camera.plane.y = 0.0;
}

/*
 Facing West: dir = (-1, 0), plane = (0, -1)
*/
static void	set_up_dir_and_plane_for_west(t_data *data)
{
    data->camera.dir.x   = -1.0;
    data->camera.dir.y   = 0.0;
    data->camera.plane.x = 0.0;
    data->camera.plane.y = 1.0;
}
/*
Facing East: dir = (1, 0), plane = (0, 1)
*/
static void	set_up_dir_and_plane_for_east(t_data *data)
{
    data->camera.dir.x   = 1.0;
    data->camera.dir.y   = 0.0;
    data->camera.plane.x = 0.0;
    data->camera.plane.y = -1.0;
}


/*
Initialize camera dir/plane from a spawn direction ('N','S','W','E')
*/
void	set_up_camera_dir_and_plane(t_data *data, char direction)
{
    if (direction == 'N')
        set_up_dir_and_plane_for_north(data);
    else if (direction == 'S')
        set_up_dir_and_plane_for_south(data);
    else if (direction == 'W')
        set_up_dir_and_plane_for_west(data);
    else if (direction == 'E')
        set_up_dir_and_plane_for_east(data);
    else
        set_up_dir_and_plane_for_north(data); // fallback
}
