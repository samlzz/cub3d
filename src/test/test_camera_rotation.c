/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_camera_rotation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:49:30 by eazard            #+#    #+#             */
/*   Updated: 2025/09/09 11:53:53 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_camera_rotation(void)
{
	t_camera	camera;

	camera.pos.x = 22.0;
	camera.pos.y = 12.0;
	camera.dir.x = -1.0;
	camera.dir.y = 0.0;
	camera.plane.x = 0.0;
	camera.plane.y = 0.66;
	camera_print(camera, "before rotation");
	camera_rotate(&camera, deg_to_rad(90));
	camera_print(camera, "after rotation");
}
