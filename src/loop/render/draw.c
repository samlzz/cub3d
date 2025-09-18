/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:30:20 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/18 17:27:36 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "ft_mlx_img.h"
#include "data/data.h"
#include "render.h"

void	draw_vline(t_data *data, t_line line, uint32_t color)
{
	int		y;

	y = line.y0;
	while (y < line.y1)
	{
		ft_mlx_img_put_px(&data->mlx.img, (t_vec2i){line.column, y}, color);
		y++;
	}
}

void	draw_clear(t_img *img, uint32_t ceil_color, uint32_t floor_color)
{
	ft_mlx_img_fill(img,
		(t_vec2i){0, 0},
		(t_vec2i){WIN_WIDTH, WIN_HEIGHT / 2},
		(t_color){.value = ceil_color});
	ft_mlx_img_fill(img,
		(t_vec2i){0, WIN_HEIGHT / 2},
		(t_vec2i){WIN_WIDTH, WIN_HEIGHT},
		(t_color){.value = floor_color});
}

static uint32_t	calcul_offset_from_tex_data(t_dda_data	*dda)
{
	return ((dda->tex_img->line_len) * dda->tex_y
		+ dda->tex_x * dda->tex_img->bpp / 8);
}

/*
function contextual to textured_dda algorithm, not re usable outside
*/
void	draw_bend_with_textue(t_data *data, t_dda_data *dda)
{
	dda->y = dda->draw_start;
	while (dda->y < dda->draw_end)
	{
		dda->tex_y = (int)dda->tex_pos;
		if (dda->tex_y < 0)
			dda->tex_y = 0;
		if (dda->tex_y > dda->tex_img->height - 1)
			dda->tex_y = dda->tex_img->height - 1;
		dda->tex_pos += dda -> tex_step;
		dda->color = *(uint32_t *)(dda->tex_img->data_addr
				+ calcul_offset_from_tex_data(dda));
		if (dda->side == 1)
			dda->color = (dda->color >> 1) & 8355711;
		ft_mlx_img_put_px(&data->mlx.img, (t_vec2i){dda->x, dda->y},
			dda->color);
		dda->y++;
	}
}

/*
function contextual to untextured_dda algorithm, not re usable outside
*/
void	draw_bend_without_texture(t_data *data, t_dda_data *dda)
{
	int32_t		color;
	t_line		line;

	if (dda->side == 0)
	{
		if (dda->step.x < 0)
			color = EST_COLOR;
		else
			color = WEST_COLOR;
	}
	else if (dda->step.y < 0)
		color = NORTH_COLOR;
	else
		color = SOUTH_COLOR;
	line.column = dda->x;
	line.y0 = dda->draw_start;
	line.y1 = dda->draw_end;
	draw_vline(data, line, color);
}
