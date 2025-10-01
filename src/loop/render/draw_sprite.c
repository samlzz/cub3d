/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:11:51 by eazard            #+#    #+#             */
/*   Updated: 2025/10/01 10:12:15 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef CUB3D_BONUS

# include <stdint.h>

# include "data/window.h"
# include "render.h"
# include "ft_mlx/ft_mlx_img.h"
# include "vec/vec.h"

static int	_get_tex_y(t_sprite_rendering_data *sprite_data,
				int y, t_img *sprite_img)
{
	int			d;

	d = (int)((y - WIN_HEIGHT / 2 + sprite_data->sprite_height_on_window / 2)
			<< 8);
	return (((d * sprite_img->dim.y)
			/ sprite_data->sprite_height_on_window) >> 8);
}

static inline bool	_tex_y_is_in_sprite_img_bound(int32_t tex_y,
				t_img *sprite_img)
{
	return (tex_y >= 0 && tex_y < sprite_img->dim.y);
}

static void	_draw_sprite_band(t_data *data,
				t_sprite_rendering_data *sprite_data, int band)
{
	int32_t		y;
	uint32_t	color;
	t_img		*sprite_img;

	sprite_img = &sprite_data->frame_asset_img;
	sprite_data->tex_pos.x = (int)((band \
						- (sprite_data->sprite_center_x_screen_space \
						- ((double)sprite_data->sprite_width_on_window) / 2)) \
					* ((double)sprite_img->dim.x \
						/ (double)sprite_data->sprite_width_on_window));
	if (sprite_data -> tex_pos.x < 0
		|| sprite_data->tex_pos.x >= sprite_img->dim.x)
		return ;
	y = sprite_data->left_bound.y;
	while (y < sprite_data->right_bound.y)
	{
		sprite_data->tex_pos.y = _get_tex_y(sprite_data, y, sprite_img);
		if (_tex_y_is_in_sprite_img_bound(sprite_data->tex_pos.y, sprite_img))
		{
			color = ft_mlx_img_get_px(sprite_img, sprite_data->tex_pos);
			if ((color != 0x0dff00))
				ft_mlx_img_put_px(&data->mlx.game, (t_vec2i){band, y}, color);
		}
		y++;
	}
}

void	draw_sprite(t_data *data, t_sprite_rendering_data *sprite_data)
{
	int32_t	band;

	band = sprite_data->left_bound.x;
	while (band < sprite_data->right_bound.x)
	{
		if (sprite_data->camera_space_coordinate.y < data->zbuf[band])
			_draw_sprite_band(data, sprite_data, band);
		band++;
	}
}

#endif
