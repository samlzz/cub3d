/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_img_putrect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:23:43 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/27 15:25:14 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec/vec.h"
#include "ft_mlx_img.h"

void	ft_mlx_img_put_rect(t_img *img, int32_t thick, t_color color)
{
	t_vec2i	top_l;
	t_vec2i	a;
	t_vec2i	b;

	if (thick <= 0)
		return ;
	top_l = (t_vec2i){0};
	a = top_l;
	b = (t_vec2i){img->dim.x, top_l.y + thick};
	ft_mlx_img_put_square(img, a, b, color);
	a = (t_vec2i){top_l.x, img->dim.y - thick};
	b = img->dim;
	ft_mlx_img_put_square(img, a, b, color);
	a = (t_vec2i){top_l.x, top_l.y + thick};
	b = (t_vec2i){top_l.x + thick, img->dim.y - thick};
	ft_mlx_img_put_square(img, a, b, color);
	a = (t_vec2i){img->dim.x - thick, top_l.y + thick};
	b = (t_vec2i){img->dim.x, img->dim.y - thick};
	ft_mlx_img_put_square(img, a, b, color);
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
