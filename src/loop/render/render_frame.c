/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:37:25 by eazard            #+#    #+#             */
/*   Updated: 2025/09/20 11:07:17 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>

#include "color.h"
#include "cubmap.h"
#include "data/data.h"
#include "ft_mlx_img.h"
#include "vec/ftmath_utils.h"
#include "vec/vec.h"
#include "data/camera.h"
#include "render.h"

static inline void	_fill_one_square(t_img *img, t_vec2i square_pos, 
	int32_t size, t_color color)
{
	t_vec2i	start_px;
	t_vec2i	end_px;

	start_px = vec2i_scalar_mult(square_pos, size);
	end_px.x = start_px.x + size;
	end_px.y = start_px.y + size;
	ft_mlx_img_put_square(img, start_px, end_px, color);
}

void	render_minimap(t_img *minimap, const t_grid *grid)
{
	t_color	color;
	char	c;
	t_vec2i	i;

	i.y = 0;
	color.value = 0;
	while (i.y < grid->dim.y)
	{
		i.x = 0;
		while (i.x < grid->dim.x)
		{
			c = grid->grid[i.y][i.x];
			if (c == '1')
				color.value = C_DARK_GRAY;
			else if (c == '0')
				color.value = C_LIGHT_GRAY;
			else
				color.value = C_SPAWN;
			_fill_one_square(minimap, i, MINIMAP_SCALE, color);
			i.x++;
		}
		i.y++;
	}
}

void	render_minimap_player(t_img *minimap, int32_t map_height, t_vec2d cam_pos)
{
	t_vec2i	real_pos;
	t_color	player_color;

	player_color.value = C_PLAYER;
	real_pos.y = get_y_pos(map_height, cam_pos.y);
	real_pos.x = (int32_t)floor(cam_pos.x);
	_fill_one_square(minimap, real_pos, MINIMAP_SCALE, player_color);
}

static	t_vec2d	get_ray_dir(t_camera *cam, int32_t x)
{
	double	camera_x;

	camera_x = 2.0 * (double)x / (WIN_WIDTH - 1) - 1.0;
	return (vec2d_sum(cam->dir, 
		vec2d_scalar_mult(cam->plane, camera_x * cam->fov_factor)));
}

void	render_frame(t_data *data)
{
	t_dda_data	dda;

	render_minimap(&data->mlx.minimap, &data->map.g);
	render_minimap_player(
		&data->mlx.minimap,
		data->map.g.dim.y,
		data->camera.pos);
	draw_clear(&data->mlx.game, C_SKY_BLUE, C_BROWN);
	dda.x = 0;
	while (dda.x < WIN_WIDTH)
	{
		dda.ray_dir = get_ray_dir(&data->camera, dda.x);
		dda_algorithm(data, &dda);
		dda.x++;
	}
}
