/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:25:40 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 14:34:01 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>

#include "color.h"
#include "loop/loop.h"
#include "vec/ftmath_utils.h"
#include "vec/vec.h"
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

uint32_t	ft_mlx_img_get_px(const t_img *img, t_vec2i pos)
{
	size_t	offset;
	char	*src;

	if (pos.x < 0 || pos.y < 0
		|| pos.x >= img->dim.x || pos.y >= img->dim.y)
		return (0);
	offset = pos.y * img->line_len + pos.x * (img->bpp / 8);
	src = img->data_addr + offset;
	return (*(uint32_t *)src);
}

/* draw a horizontale line from xline.a.x to xline.b.x
	doesn't draw anything if xline.a.y != xline.b.y 
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
	double	r;
	int32_t	ymax;
	t_vec2i	curr;
	double	xr;
	double	yc;

	if (diameter <= 0)
		return ;
	if (diameter == 1)
		return (ft_mlx_img_put_px(img, center, color.value));
	r = (double)diameter * 0.5;
	ymax = (int32_t)floor(r - EPS);
	curr.y = (int32_t)floor(-r);
	r *= r;
	while (curr.y <= ymax)
	{
		yc = (double)curr.y + 0.5;
		xr = sqrt(r - yc * yc);
		curr.x = (int32_t)floor(xr - 0.5);
		ft_mlx_img_put_span(img, (t_vec2iv2){
			(t_vec2i){ center.x - curr.x, center.y + curr.y},
			vec2i_sum(center, curr)
		}, color);
		curr.y++;
	}
}
