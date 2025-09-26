/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:25:40 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/26 14:27:07 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "color.h"
#include "vec/ftmath_utils.h"
#include "vec/vec.h"
#include "data/data.h"
#include "ft_mlx_img.h"

void	ft_mlx_img_put_px(t_img *img, t_vec2i pos, uint32_t color)
{
	size_t	offset;
	char	*dst;

	if (pos.x < 0 || pos.y < 0
		|| pos.x >= img->dim.x
		|| pos.y >= img->dim.y)
		return ;
	offset = pos.y * img->line_len + pos.x * (img->bpp / 8);
	dst = img->data_addr + offset;
	*(uint32_t *)dst = color;
}

/* draw a horizontale line from yline.a.x to yline.b.x
	doesn't draw anything if yline.a.y != yline.b.y 
*/
void	ft_mlx_img_put_span(t_img *img, t_vec2iv2 xline, t_color color)
{
	int32_t	x;

	if (xline.a.y != xline.b.y)
		return ;
	if (xline.a.x > xline.b.x)
		ftm_swap(&xline.a.x, &xline.b.x);
	x = xline.a.x;
	while (x <= xline.b.x)
	{
		ft_mlx_img_put_px(img, (t_vec2i){x, xline.a.y}, color.value);
		x++;
	}
}


void	ft_mlx_img_put_sphere(t_img *img, t_vec2i center, int32_t diameter, 
	t_color color)
{
	int32_t	r;
	int32_t	r_square;
	t_vec2i	delta;

	if (diameter == 1)
		ft_mlx_img_put_px(img, center, color.value);
	r = (diameter - 1) / 2;
	r_square = r * r;
	delta.y = -r;
	while (delta.y <= r)
	{
		delta.x = -r;
		while (delta.x <= r)
		{
			if (delta.x * delta.x + delta.y * delta.y <= r_square)
				ft_mlx_img_put_px(img, vec2i_sum(center, delta), color.value);
			delta.x++;
		}
		delta.y++;
	}
}

void	ft_mlx_img_put_square(t_img *img, t_vec2i start,
			const t_vec2i end, const t_color filled)
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

void	ft_mlx_img_fill(t_img *img, t_vec2i start, const t_color filled)
{
	ft_mlx_img_put_square(img, start, img->dim, filled);
}