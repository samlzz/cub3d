/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_camera_rotation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:49:30 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 16:23:11 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	test_camera_rotation(void)
{
	t_camera	camera;

	camera.pos.x = 22.0;
	camera.pos.y = 12.0;
	camera.dir.x = -1.0;
	camera.dir.y = 0.0;
	camera.plane.x = 0.0;
	camera.plane.y = 0.66;
	camera_print(camera);
	camera_rotate(&camera, deg_to_rad(90));
	camera_print(camera);
}
