/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:55:15 by eazard            #+#    #+#             */
/*   Updated: 2025/09/12 14:38:29 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

/*angle is in radian*/
void	camera_rotate(t_camera *camera, double angle)
{
	vec_rotate(&camera->dir, angle);
	vec_rotate(&camera->plane, angle);
}

void	camera_left_rotate(t_camera *camera, double angle)
{
	camera_rotate(camera, angle);
}

void	camera_right_rotate(t_camera *camera, double angle)
{
	camera_rotate(camera, -angle);
}
