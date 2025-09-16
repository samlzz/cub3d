/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:56:57 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 19:59:00 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vec/vec.h"

typedef struct s_data	t_data;
typedef struct s_grid	t_grid;
typedef struct s_camera	t_camera;

struct s_camera
{
	t_vec2d	pos;
	t_vec2d	dir;
	t_vec2d	plane;
	double	current_frame_time;
	double	last_frame_time;
	double	fov_factor;
	double	zbuf;
};

void	camera_init(t_camera *cam, const t_grid map);

/*print*/
void	camera_print(t_camera camera);

/*rotate*/
void	camera_rotate(t_camera *camera, double angle);
void	camera_left_rotate(t_camera *camera, double angle);
void	camera_right_rotate(t_camera *camera, double angle);

#endif