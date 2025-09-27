/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_img_puttriangle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:32:45 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/27 13:53:23 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>

#include "ft_mlx_img.h"
#include "color.h"
#include "vec/ftmath_utils.h"
#include "vec/vec.h"

#define AB	0
#define BC	1
#define CA	2

static int64_t	_edge_fn(t_vec2i lvertice, t_vec2i rvertice, t_vec2i curr_p)
{
	int64_t	v;
	int64_t	wx;
	int64_t	wy;

	wx = (int64_t)(curr_p.x - lvertice.x);
	wy = (int64_t)(curr_p.y - lvertice.y);
	v = wx * (int64_t)(rvertice.y - lvertice.y)
		- wy * (int64_t)(rvertice.x - lvertice.x);
	return (v);
}

static inline bool	_is_top_left(t_vec2i a, t_vec2i b)
{
	t_vec2i	delta;

	delta = vec2i_minus(b, a);
	return ((delta.y > 0) || (delta.y == 0 && delta.x < 0));
}

static void	_bbox_from_tri(t_vec2iv3 t, t_vec2i img, t_vec2i *mn, t_vec2i *mx)
{
	t_vec2i	minv;
	t_vec2i	maxv;

	minv.x = ftm_min3(t.a.x, t.b.x, t.c.x);
	minv.y = ftm_min3(t.a.y, t.b.y, t.c.y);
	maxv.x = ftm_max3(t.a.x, t.b.x, t.c.x);
	maxv.y = ftm_max3(t.a.y, t.b.y, t.c.y);
	if (minv.x < 0)
		minv.x = 0;
	if (minv.y < 0)
		minv.y = 0;
	if (maxv.x >= img.x)
		maxv.x = img.x - 1;
	if (maxv.y >= img.y)
		maxv.y = img.y - 1;
	*mn = minv;
	*mx = maxv;
}

static inline bool	_is_px_printable(t_vec2iv3 tri, t_vec2i curr_p, uint8_t tl)
{
	t_vec3l	e;

	e.x = _edge_fn(tri.a, tri.b, curr_p);
	e.y = _edge_fn(tri.b, tri.c, curr_p);
	e.z = _edge_fn(tri.c, tri.a, curr_p);
	return (
		(e.x > 0 || (!e.x && (tl >> AB) & 1))
		&& (e.y > 0 || (!e.y && (tl >> BC) & 1))
		&& (e.z > 0 || (!e.z && (tl >> CA) & 1))
	);
}

void	ft_mlx_img_put_triangle(t_img *img, t_vec2iv3 tri, t_color color)
{
	t_vec2i	min;
	t_vec2i	max;
	t_vec2i	p;
	uint8_t	top_left;
	int64_t	area;

	area = _edge_fn(tri.a, tri.b, tri.c);
	if (!area)
		return ;
	(void)(area < 0 && (vec2i_swap(&tri.b, &tri.c), 1));
	_bbox_from_tri(tri, img->dim, &min, &max);
	top_left = (_is_top_left(tri.a, tri.b) | (_is_top_left(tri.b, tri.c) << 1)
			| (_is_top_left(tri.c, tri.a) << 2));
	p.y = min.y;
	while (p.y <= max.y)
	{
		p.x = min.x;
		while (p.x <= max.x)
		{
			if (_is_px_printable(tri, p, top_left))
				ft_mlx_img_put_px(img, p, color.value);
			p.x++;
		}
		p.y++;
	}
}
