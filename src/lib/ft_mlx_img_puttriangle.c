/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_img_puttriangle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:32:45 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/26 14:08:38 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "ft_mlx_img.h"
#include "color.h"
#include "vec/vec.h"

/* sort in ascending order
	v.a = top, v.b = middle, v.c = bottom 
*/
static void	sort_by_y(t_vec2iv3 *v)
{
	if (v->a.y > v->b.y)
		vec2i_swap(&v->a, &v->b);
	if (v->a.y > v->c.y)
		vec2i_swap(&v->a, &v->c);
	if (v->b.y > v->c.y)
		vec2i_swap(&v->b, &v->c);
}

/* tri.a.y == tri.b.y : flat bottom, tri.c to top */
static void	_fill_flat_bottom(t_img *img, t_vec2iv3 tri, t_color color)
{
	double dx0;
	double dx1;
	t_vec2d	left;
	t_vec2d	right;

	dx0 = (double)(tri.c.x - tri.a.x) / (double)(tri.c.y - tri.a.y);
	dx1 = (double)(tri.c.x - tri.b.x) / (double)(tri.c.y - tri.b.y);
	left = (t_vec2d){tri.a.x, tri.a.y};
	right = (t_vec2d){tri.b.x, tri.b.y};
	while (left.y <= tri.c.y)
	{
		ft_mlx_img_put_span(img,
			(t_vec2iv2){
				vec2d_round(left, false),
				vec2d_round(right, false)},
			color);
		left = vec2d_sum(left, (t_vec2d){dx0, 1});
		right = vec2d_sum(right, (t_vec2d){dx1, 1});
	}
}

/* tri.b.y == tri.c.y : flat bottom, tri.a to top */
static void	_fill_flat_top(t_img *img, t_vec2iv3 tri, t_color color)
{
	double dx0;
	double dx1;
	t_vec2d	left;
	t_vec2d	right;

	dx0 = (double)(tri.b.x - tri.a.x) / (double)(tri.b.y - tri.a.y);
	dx1 = (double)(tri.c.x - tri.a.x) / (double)(tri.c.y - tri.a.y);
	left = (t_vec2d){tri.a.x, tri.a.y};
	right = left;
	while (left.y < tri.b.y)
	{
		ft_mlx_img_put_span(img,
			(t_vec2iv2){
				vec2d_round(left, true),
				vec2d_round(right, true)},
			color);
		left = vec2d_sum(left, (t_vec2d){dx0, 1});
		right = vec2d_sum(right, (t_vec2d){dx1, 1});
	}
}

static t_vec2i	interp_at_y(t_vec2i p0, t_vec2i p1, int y)
{
	double	t;
	t_vec2i	i;
	int32_t	dy;

	dy = (p1.y - p0.y);
	if (dy == 0)
		return ((t_vec2i){ p0.x, y });
	t = (double)(y - p0.y) / (double)dy;
	i.x = p0.x + (int)((p1.x - p0.x) * t);
	i.y = y;
	return (i);
}

void	ft_mlx_img_put_triangle(t_img *img, t_vec2iv3 triangle, t_color color)
{
	t_vec2iv3	v;
	t_vec2i		split;

	v = triangle;
	sort_by_y(&v);
	if (v.a.y == v.c.y)
	{
		ft_mlx_img_put_span(img, (t_vec2iv2){v.a, v.b}, color);
		ft_mlx_img_put_span(img, (t_vec2iv2){v.a, v.c}, color);
		return ;
	}
	if (v.b.y == v.a.y)
		return (_fill_flat_bottom(img, v, color));
	if (v.b.y == v.c.y)
		return (_fill_flat_top(img, v, color));
	split = interp_at_y(v.a, v.c, v.b.y);
	_fill_flat_top(img, (t_vec2iv3){v.a, v.b, split}, color);
	_fill_flat_bottom(img, (t_vec2iv3){v.b, split, v.c}, color);
}

