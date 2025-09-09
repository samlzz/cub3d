/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:56:57 by eazard            #+#    #+#             */
/*   Updated: 2025/09/09 12:03:04 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vec.h"

typedef struct s_camera	t_camera;

struct s_camera
{
	t_vec2d pos;
	t_vec2d	dir;
	t_vec2d	plane;
	double	current_frame_time;
	double	last_frame_time;
};

/*print*/
void	camera_print(t_camera camera, char *name);

/*rotate*/
void	camera_rotate(t_camera *camera, double angle);
void	camera_left_rotate(t_camera *camera, double angle);
void	camera_right_rotate(t_camera *camera, double angle);


#endif