/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:11:51 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 12:02:27 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "ft_mlx_img.h"

static int	get_tex_y(t_sprite_rendering_data *sprite_data,
				int y, t_img *sprite_img)
{
	int			d;

	d = (int)((y - WIN_HEIGHT / 2 + sprite_data->sprite_height_on_window / 2)
			<< 8);
	return (((d * sprite_img->height)
			/ sprite_data->sprite_height_on_window) >> 8);
}

static bool	tex_y_is_in_sprite_img_bound(t_sprite_rendering_data *sprite_data,
				t_img *sprite_img)
{
	return (sprite_data->tex_y >= 0
		&& sprite_data->tex_y < sprite_img->height);
}

static inline uint32_t	get_texel(t_img *img, int tex_x, int tex_y)
{
	return (*(uint32_t *)(img->data_addr + tex_y * img->line_len
		+ tex_x * (img->bpp / 8)));
}

static void	draw_sprite_band(t_data *data,
				t_sprite_rendering_data *sprite_data, int band)
{
	int			y;
	uint32_t	color;
	t_img		*sprite_img;

	sprite_img = &sprite_data->frame_asset_img;
	sprite_data->tex_x = (int)((band \
							- (sprite_data->sprite_center_x_screen_space \
							- sprite_data->sprite_width_on_window / 2)) \
					* ((double)sprite_img->width \
						/ (double)sprite_data->sprite_width_on_window));
	if (sprite_data -> tex_x < 0 || sprite_data->tex_x >= sprite_img->width)
		return ;
	y = sprite_data->left_bound.y;
	while (y < sprite_data->right_bound.y)
	{
		sprite_data->tex_y = get_tex_y(sprite_data, y, sprite_img);
		if (tex_y_is_in_sprite_img_bound(sprite_data, sprite_img))
		{
			color = get_texel(sprite_img,
					sprite_data->tex_x, sprite_data->tex_y);
			if ((color & 0x00FFFFFF) != 0)
				ft_mlx_img_put_px(&data->mlx.img, (t_vec2i){band, y}, color);
		}
		y++;
	}
}

void	draw_sprite(t_data *data, t_sprite_rendering_data *sprite_data)
{
	int				band;

	band = sprite_data->left_bound.x;
	while (band < sprite_data->right_bound.x)
	{
		if (sprite_data->camera_space_coordinate.y < data->zbuf[band])
			draw_sprite_band(data, sprite_data, band);
		band++;
	}
}
