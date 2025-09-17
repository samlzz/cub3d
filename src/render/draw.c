/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:30:20 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/17 17:47:54 by sliziard         ###   ########.fr       */
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
		(t_color){.value=ceil_color});
	ft_mlx_img_fill(img, 
		(t_vec2i){0, WIN_HEIGHT / 2},
		(t_vec2i){WIN_WIDTH, WIN_HEIGHT},
		(t_color){.value=floor_color});
}
