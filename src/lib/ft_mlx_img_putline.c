/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_img_putline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 07:19:31 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/26 14:05:32 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "data/data.h"
#include "ft_mlx_img.h"
#include "vec/vec.h"
#include <stdint.h>
#include <stdlib.h>

static void	slope_less_one(t_img *img, t_vec2i d, t_vec2iv2 line, t_color color)
{
	int32_t	decision;
	int32_t	i;
	bool	tern;

	i = 0;
	decision = 2 * abs(d.y) - abs(d.x);
	while (i < abs(d.x))
	{
		tern = d.x > 0;
		(void)((tern && line.a.x++) || (!tern && line.a.x--));
		if (decision < 0)
			decision += 2 * abs(d.y);
		else
		{
			tern = d.y > 0;
			(void)((tern && line.a.y++) || (!tern && line.a.y--));
			decision += 2 * abs(d.y) - 2 * abs(d.x);
		}
		ft_mlx_img_put_px(img, line.a, color.value);
		i++;
	}
}

static void	slope_greater_one(t_img *img, t_vec2i d, t_vec2iv2 line, t_color color)
{
	int32_t	decision;
	int32_t	i;
	bool	tern;

	i = 0;
	decision = 2 * abs(d.x) - abs(d.y);
	while (i < abs(d.y))
	{
		tern = d.y > 0;
		(void)((tern && line.a.y++) || (!tern && line.a.y--));
		if (decision < 0)
			decision += 2 * abs(d.x);
		else
		{
			tern = d.x > 0;
			(void)((tern && line.a.x++) || (!tern && line.a.x--));
			decision += 2 * abs(d.x) - 2 * abs(d.y);
		}
		ft_mlx_img_put_px(img, line.a, color.value);
		i++;
	}
}

int32_t	ft_mlx_img_put_line(t_img *img, t_vec2i start, t_vec2i end, t_color color)
{
	t_vec2iv2	line;
	t_vec2i		delta;
	int32_t		px_count;

	line.a = start;
	line.b = end;
	delta = vec2i_minus(end, start);
	if (abs(delta.x) > abs(delta.y))
	{
		slope_less_one(img, delta, line, color);
		px_count = delta.x;
	}
	else
	{
		slope_greater_one(img, delta, line, color);
		px_count = delta.y;
	}
	return (px_count);
}
