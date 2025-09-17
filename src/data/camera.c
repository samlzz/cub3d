/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:55:15 by eazard            #+#    #+#             */
/*   Updated: 2025/09/17 17:38:24 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "camera.h"
#include "vec/vec.h"

/*angle is in radian*/
void	camera_rotate(t_camera *camera, double angle)
{
	vec2d_rotate(&camera->dir, angle);
	vec2d_rotate(&camera->plane, angle);
}

void	camera_left_rotate(t_camera *camera, double angle)
{
	camera_rotate(camera, angle);
}

void	camera_right_rotate(t_camera *camera, double angle)
{
	camera_rotate(camera, -angle);
}

void	camera_print(t_camera camera)
{
	fprintf(stderr, "\rPOS(%.2f, %.2f) DIR(%.2f, %.2f) PLANE(%.2f, %.2f) ",
		camera.pos.x, camera.pos.y,
		camera.dir.x, camera.dir.y,
		camera.plane.x, camera.plane.y);
	fflush(stderr);
}
