/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:05:06 by eazard            #+#    #+#             */
/*   Updated: 2025/09/04 17:38:08 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	camera_print(t_camera camera, char *name)
{
	printf("%s\n", name);
	printf("position\n");
	printf("x = %f\n", camera.pos_x);
	printf("y = %f\n", camera.pos_y);
	print_vec2d(camera.dir, "dir");
	print_vec2d(camera.plane, "plane");
}
