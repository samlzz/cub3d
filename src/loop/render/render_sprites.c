/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:49:28 by eazard            #+#    #+#             */
/*   Updated: 2025/09/29 13:49:48 by eazard           ###   ########.fr       */
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

static void	sprite_camera_transform(t_camera *cam, t_sprite *sprite,
					double *tX, double *tY)
{
	double	invdet;
	double	dx;
	double	dy;

	dx = sprite->x - cam->pos.x;
	dy = sprite->y - cam->pos.y;
	invdet = 1.0 / (cam->plane.x * cam->dir.y - cam->dir.x * cam->plane.y);
	*tX = invdet * (cam->dir.y * dx - cam->dir.x * dy);
	*tY = invdet * (-cam->plane.y * dx + cam->plane.x * dy);
}

static int	_ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	set_up_sprite_order_and_dist(t_data *data)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < SPRITE_NB)
	{
		data->map.sprite_order[i] = i;
		dx = data->camera.pos.x - data->map.sprites[i].x;
		dy = data->camera.pos.y - data->map.sprites[i].y;
		data->map.sprite_distance_square[i] = dx * dx + dy * dy;
		i++;
	}
}

void	sort_sprite(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < SPRITE_NB - 1)
	{
		j = 0;
		while (j < SPRITE_NB - 1 - i)
		{
			if (data->map.sprite_distance_square[data->map.sprite_order[j]]
				< data->map.sprite_distance_square
				[data->map.sprite_order[j + 1]])
				_ft_swap(&data->map.sprite_order[j],
					&data->map.sprite_order[j + 1]);
			j++;
		}
		i++;
	}
}

static inline uint32_t	get_texel(t_img *img, int tx, int ty)
{
	return (*(uint32_t *)(img->data_addr + ty * img->line_len
			+ tx * (img->bpp / 8)));
}

static void	get_camera_space_coordinate(t_camera *cam, t_sprite *sprite,
					t_vec2d *out)
{
	double	invdet;
	double	dx;
	double	dy;

	dx = sprite->x - cam->pos.x;
	dy = sprite->y - cam->pos.y;
	invdet = 1.0 / (cam->plane.x * cam->dir.y - cam->dir.x * cam->plane.y);
	out->x = invdet * (cam->dir.y * dx - cam->dir.x * dy);
	out->y = invdet * (-cam->plane.y * dx + cam->plane.x * dy);
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

/* --- 2.5: choisir la frame (ici: frame 0, prêt pour anim) --- */
static void	select_frame_img(t_asset_data *sprite_data, t_sprite *sprite)
{
	/* TODO anim: sprite_data->frame_index = (int)(time_s * fps) % sprite->img_nb; */
	sprite_data->frame_index = 0;
	sprite_data->frame_asset_img = &sprite->imgs[sprite_data->frame_index];
}

/* --- 2.6: dessiner une “stripe” (colonne) du sprite --- */
static void	draw_sprite_stripe(t_data *data, t_asset_data *sprite_data, int sprite)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		d;
	uint32_t	color;
	t_img	*tex;

	tex = &sprite_data->frame_asset_img;
	tex_x = (int)((sprite - (-sprite_data->sprite_width / 2 + sprite_data->sprite_center_x_screen_space))
			* (double)tex->width / (double)sprite_data->sprite_width);
	y = sprite_data->left_bound.y;
	while (y < sprite_data->right_bound.y)
	{
		d = (y * 256) - (WIN_HEIGHT * 128) + (sprite_data->sprite_height * 128);
		tex_y = (d * tex->height) / sprite_data->sprite_height / 256;
		if (tex_x >= 0 && tex_x < tex->width && tex_y >= 0 && tex_y < tex->height)
		{
			color = get_texel(tex, tex_x, tex_y);
			if ((color & 0x00FFFFFF) != 0)
				put_pixel_in_buffer(&data->mlx.img, sprite, y, color);
		}
		y++;
	}
}

// void	render_sprites(t_data *data)
// {
// 	int		i;
// 	int		printed_sprit_index;
// 	t_vec2d	camera_space_coordinate;
// 	int		sprite_center_x_screen_space;
// 	int		sprite_height;
// 	int		sprite_width;
// 	t_vec2i	left_bound;
// 	t_vec2i	right_bound;
// 	t_img	*frame_asset_img;

// 	i = 0;
// 	while (i < SPRITE_NB)
// 	{
// 		printed_sprit_index = data->map.sprite_order[i];
// 		sprite_camera_transform(&data->camera,
// 			&data->map.sprites[printed_sprit_index],
// 			&camera_space_coordinate);
// 		if (camera_space_coordinate.y > 0.0001)
// 		{
// 			sprite_center_x_screen_space = (int)((WIN_WIDTH / 2.0)
// 				* (1.0 + camera_space_coordinate.x / camera_space_coordinate.y));
// 			sprite_height = (int)(WIN_HEIGHT / camera_space_coordinate.y);
// 			sprite_width = sprite_height; /* carré par défaut */

// 			left_bound.y  = -sprite_height / 2 + WIN_HEIGHT / 2;
// 			right_bound.y =  sprite_height / 2 + WIN_HEIGHT / 2;
// 			left_bound.x  = -sprite_width / 2 + sprite_center_x_screen_space;
// 			right_bound.x =  sprite_width / 2 + sprite_center_x_screen_space;

// 			clampi(&left_bound.y, 0, WIN_HEIGHT);
// 			clampi(&right_bound.y, 0, WIN_HEIGHT);
// 			clampi(&left_bound.x, 0, WIN_WIDTH);
// 			clampi(&right_bound.x, 0, WIN_WIDTH);

// 			/* TODO anim: choisir l’index de frame */
// 			frame_asset_img = &data->map.sprites[printed_sprit_index].imgs[0];

// 			while (left_bound.x < right_bound.x)
// 			{
// 				/* Avec zbuffer plus tard:
// 				   if (camera_space_coordinate.y < data->zbuffer[left_bound.x]) { ... } */
// 				draw_sprite_stripe(data, &data->mlx.img, frame_asset_img,
// 					left_bound.x, left_bound, right_bound,
// 					sprite_width, sprite_height,
// 					sprite_center_x_screen_space);
// 				left_bound.x++;
// 			}
// 		}
// 		i++;
// 	}
// }
