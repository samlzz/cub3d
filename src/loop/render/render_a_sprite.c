/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_a_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:46:11 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 12:07:49 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	ft_clamp_i(int *value, int min, int max)
{
	if (*value < min)
		*value = min;
	if (*value > max)
		*value = max;
}

/* --- 2.2: tailles & position écran --- */
static void	get_sprite_size_and_location_on_window(
				t_sprite_rendering_data *sprite_data)
{
	sprite_data->sprite_center_x_screen_space = (int)((WIN_WIDTH / 2.0)
			* (1.0 + sprite_data->camera_space_coordinate.x
				/ sprite_data->camera_space_coordinate.y));
	sprite_data->sprite_height_on_window
		= (int)(WIN_HEIGHT / sprite_data->camera_space_coordinate.y);
	sprite_data->sprite_width_on_window = sprite_data->sprite_height_on_window;
}

/* --- 2.3: bornes (avant clamp) --- */
static void	set_sprite_bound_on_window(t_sprite_rendering_data *sprite_data)
{
	sprite_data->left_bound.y
		= -sprite_data->sprite_height_on_window / 2 + WIN_HEIGHT / 2;
	sprite_data->right_bound.y
		= sprite_data->sprite_height_on_window / 2 + WIN_HEIGHT / 2;
	sprite_data->left_bound.x
		= -sprite_data->sprite_width_on_window / 2 \
			+ sprite_data->sprite_center_x_screen_space;
	sprite_data->right_bound.x
		= sprite_data->sprite_width_on_window / 2 \
			+ sprite_data->sprite_center_x_screen_space;
}

/* --- 2.4: clamp dans la fenêtre --- */
static void	clamp_sprite_bound_within_window_limits(
				t_sprite_rendering_data *sprite_data)
{
	ft_clamp_i(&sprite_data->left_bound.y, 0, WIN_HEIGHT);
	ft_clamp_i(&sprite_data->right_bound.y, 0, WIN_HEIGHT);
	ft_clamp_i(&sprite_data->left_bound.x, 0, WIN_WIDTH);
	ft_clamp_i(&sprite_data->right_bound.x, 0, WIN_WIDTH);
}

void	render_a_sprit(t_data *data, t_sprite_rendering_data *sprite_data,
			t_sprite *printed_sprite)
{
	get_sprite_size_and_location_on_window(sprite_data);
	set_sprite_bound_on_window(sprite_data);
	clamp_sprite_bound_within_window_limits(sprite_data);
	select_sprite_frame_img(data, sprite_data, printed_sprite);
	draw_sprite(data, sprite_data);
}
