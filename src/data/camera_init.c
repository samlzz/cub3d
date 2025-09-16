/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:44:59 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 19:58:38 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "cubmap.h"
#include "data.h"
#include "camera.h"
#include "test/test.h"
#include "vec/vec.h"
#include "parsing/parse_utils.h"

static int16_t	_dir_to_angle(char c, double *theta)
{
	if (c == 'E')
		*theta = 0.0;			/* +X */
	else if (c == 'N')
		*theta = -M_PI / 2.0;	/* -Y */
	else if (c == 'W')
		*theta = M_PI;			/* -X */
	else if (c == 'S')
		*theta = M_PI / 2.0;	/* +Y */
	else
		return (1);
	return (0);
}

static void	_set_up_camera_vecs(t_camera *c, int32_t map_h, t_vec2i pos, char dir)
{
	double	th;
	double	cs;
	double	sn;

	if (UNTEXTURED_RAYCASTING_DEBUG)
		fprintf(stderr, "x = %d, y = %d\n", pos.x, pos.y);
	c->pos.x = (double)pos.x + 0.5;
	c->pos.y = (double)(map_h - (pos.y + 1)) + 0.5; // ?dimension va de 1 a dim.y. , y va de 0 a dim.y -1 , donc je fais + 1 dans le calcule
	if (UNTEXTURED_RAYCASTING_DEBUG)
		fprintf(stderr, "camera.pos.x = %f, camera.pos.y = %f\n", c->pos.x, c->pos.y);
	if (_dir_to_angle(dir, &th))
		return ;
	cs = cos(th);
	sn = sin(th);
	c->dir.x = cs;
	c->dir.y = sn;
	c->plane.x = -sn * FOV_FACTOR;
	c->plane.y = cs * FOV_FACTOR;
}

static void	deduce_cam_setting_from_player_pos(t_camera *cam, const t_grid map)
{
	char	c;
	t_vec2i	i;

	i.y = 0;
	while (i.y < map.dim.y)
	{
		i.x = 0;
		if (UNTEXTURED_RAYCASTING_DEBUG)
				fprintf(stderr, "%s\n", map.grid[i.y]);
		while (i.x < map.dim.x)
		{
			c = map.grid[i.y][i.x];
			if (ft_is_walkable(c) && c != ' ')
				_set_up_camera_vecs(cam, map.dim.y, i, c);
			i.x++;
		}
		i.y++;
	}
}

void	camera_init(t_camera *cam, const t_grid map)
{
	deduce_cam_setting_from_player_pos(cam, map);
	cam->fov_factor = FOV_FACTOR;
}
