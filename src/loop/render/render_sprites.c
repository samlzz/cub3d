/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:49:28 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 09:32:34 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"

static void	ft_clamp_i(int *value, int min, int max)
{
	if (*value < min)
		*value = min;
	if (*value > max)
		*value = max;
}

// static void	sprite_camera_transform(t_camera *cam, t_sprite *sprite,
// 					double *tX, double *tY)
// {
// 	double	invdet;
// 	double	dx;
// 	double	dy;

// 	dx = sprite->x - cam->pos.x;
// 	dy = sprite->y - cam->pos.y;
// 	invdet = 1.0 / (cam->plane.x * cam->dir.y - cam->dir.x * cam->plane.y);
// 	*tX = invdet * (cam->dir.y * dx - cam->dir.x * dy);
// 	*tY = invdet * (-cam->plane.y * dx + cam->plane.x * dy);
// }

static void	get_camera_space_coordinate(t_camera *cam, t_sprite *sprite,
					t_vec2d *out)
{
	double	invdet;
	double	dx;
	double	dy;

	dx = sprite->x - cam->pos.x;
	dy = sprite->y - cam->pos.y;
	invdet = 1.0 / (cam->plane.x * FOV_FACTOR * cam->dir.y - cam->dir.x * cam->plane.y * FOV_FACTOR);
	out->x = invdet * (cam->dir.y * dx - cam->dir.x * dy);
	out->y = invdet * (-cam->plane.y * dx  * FOV_FACTOR + cam->plane.x * dy * FOV_FACTOR);
}

/* --- 2.2: tailles & position écran --- */
static void	get_sprite_size_and_location_data(t_asset_data *sprite_data)
{
	sprite_data->sprite_center_x_screen_space = (int)((WIN_WIDTH / 2.0)
			* (1.0 + sprite_data->camera_space_coordinate.x
				/ sprite_data->camera_space_coordinate.y));
	sprite_data->sprite_height
		= (int)(WIN_HEIGHT / sprite_data->camera_space_coordinate.y);
	sprite_data->sprite_width = sprite_data->sprite_height;
}

/* --- 2.3: bornes (avant clamp) --- */
static void	set_sprite_bound(t_asset_data *sprite_data)
{
	sprite_data->left_bound.y
		= -sprite_data->sprite_height / 2 + WIN_HEIGHT / 2;
	sprite_data->right_bound.y
		= sprite_data->sprite_height / 2 + WIN_HEIGHT / 2;
	sprite_data->left_bound.x
		= -sprite_data->sprite_width / 2 \
			+ sprite_data->sprite_center_x_screen_space;
	sprite_data->right_bound.x
		= sprite_data->sprite_width / 2 \
			+ sprite_data->sprite_center_x_screen_space;
}

/* --- 2.4: clamp dans la fenêtre --- */
static void	clamp_sprite_bound_within_window_limits(t_asset_data *sprite_data)
{
	ft_clamp_i(&sprite_data->left_bound.y, 0, WIN_HEIGHT);
	ft_clamp_i(&sprite_data->right_bound.y, 0, WIN_HEIGHT);
	ft_clamp_i(&sprite_data->left_bound.x, 0, WIN_WIDTH);
	ft_clamp_i(&sprite_data->right_bound.x, 0, WIN_WIDTH);
}

static inline bool sprint_isnt_behind_player(t_asset_data sprite_data)
{
	return (sprite_data.camera_space_coordinate.y > 0.0001);
}

void	render_sprites(t_data *data)
{
	t_asset_data	sprite_data;
	t_sprite		*printed_sprite;
	int				i;

	i = 0;
	while (i < SPRITE_NB)
	{
		sprite_data.printed_sprit_id = data->map.sprite_order[i];
		printed_sprite = &data->map.sprites[sprite_data.printed_sprit_id];
		get_camera_space_coordinate(&data->camera, printed_sprite,
			 &sprite_data.camera_space_coordinate);
		if (sprint_isnt_behind_player(sprite_data))
		{
			get_sprite_size_and_location_data(&sprite_data);
			set_sprite_bound(&sprite_data);
			clamp_sprite_bound_within_window_limits(&sprite_data);
			select_frame_img(data, &sprite_data, printed_sprite);
			draw_sprite(data, &sprite_data);
		}
		i++;
	}
}
