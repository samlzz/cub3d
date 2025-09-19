/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:09:58 by eazard            #+#    #+#             */
/*   Updated: 2025/09/19 11:09:00 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "data/camera.h"
#include "vec/vec.h"

void	vec2d_print(t_vec2d vec, char *name)
{
	printf("%s: (x: %.2f, y: %.2f)\n", name, vec.x, vec.y);
}

void	vec2i_print(t_vec2i vec, char *name)
{
	printf("%s: (x: %i, y: %i)\n", name, vec.x, vec.y);
}

void	camera_print(t_camera camera)
{
	printf("__Camera__\n");
	vec2d_print(camera.pos, "POS");
	vec2d_print(camera.dir, "DIR");
	vec2d_print(camera.plane, "PLANE");
	printf("________");
	fflush(stderr);
}
