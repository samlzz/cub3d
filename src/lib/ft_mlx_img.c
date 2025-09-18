/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:25:40 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/17 16:59:45 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "color.h"
#include "vec/vec.h"
#include "data/data.h"

void	ft_mlx_img_put_px(t_img *img, t_vec2i pos, uint32_t color)
{
	size_t	i;

	i = (pos.y * img->line_len + pos.x * (img->bpp / 8));
	img->data_addr[i] = color;
}

void	ft_mlx_img_fill(t_img *img, t_vec2i start, const t_vec2i end, const t_color filled)
{
	int32_t	w;

	w = start.x;
	while (start.y < end.y)
	{
		start.x = w;
		while (start.x < end.x)
		{
			ft_mlx_img_put_px(img, start, filled.value);
			start.x++;
		}
		start.y++;
	}
}
