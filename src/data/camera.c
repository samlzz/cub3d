/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:55:15 by eazard            #+#    #+#             */
/*   Updated: 2025/09/19 10:50:36 by sliziard         ###   ########.fr       */
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
