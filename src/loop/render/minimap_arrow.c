/* ************************************************************************** */
/* Helpers triangle pour flèche de direction (norme 42 friendly)             */
/* ************************************************************************** */

#include "ft_mlx/ft_mlx_img.h"
#include "color.h"
#include "loop/loop.h"
#include "minimap.h"
#include "vec/vec.h"
#include <stdint.h>

static inline t_vec2d	_tri_centroid(t_vec2iv3 tri)
{
	t_vec2d g;

	g.x = (tri.a.x + tri.b.x + tri.c.x) / 3.0;
	g.y = (tri.a.y + tri.b.y + tri.c.y) / 3.0;
	return (g);
}

static t_vec2i	_expand_from_centroid(t_vec2i p, t_vec2d g, int32_t px)
{
	t_vec2d	v;
	double	m;

	v.x = (double)p.x - g.x;
	v.y = (double)p.y - g.y;
	m = vec2d_get_norm(v);
	if (m < EPS)
		m = 1.0;
	v.x = v.x / m * px;
	v.y = v.y / m * px;
	return (vec2d_round((t_vec2d){ p.x + v.x, p.y + v.y }, true));
}

static inline t_vec2iv3	_grow_triangle(t_vec2iv3 tri, int32_t border_px)
{
	t_vec2iv3	out;
	t_vec2d		g;

	g = _tri_centroid(tri);
	out.a = _expand_from_centroid(tri.a, g, border_px);
	out.b = _expand_from_centroid(tri.b, g, border_px);
	out.c = _expand_from_centroid(tri.c, g, border_px);
	return (out);
}

t_vec2iv3	arrow_triangle_build(t_vec2i player, t_vec2d u, t_arrow_len L)
{
	t_vec2d		n;
	t_vec2d		tmp;
	t_vec2i		tip;
	t_vec2i		base;
	t_vec2iv3	tri;

	n = (t_vec2d){ -u.y, u.x };
	tmp = vec2d_scalar_mult(u, L.arrow_depth);
	tip = vec2i_sum(player, vec2d_round(tmp, true));
	tmp = vec2d_scalar_mult(u, L.head_len);
	base = vec2i_minus(tip, vec2d_round(tmp, true));
	tmp = vec2d_scalar_mult(n, L.head_wid);
	tri.a = tip;
	tri.b = vec2i_sum(base, vec2d_round(tmp, true));
	tri.c = vec2i_minus(base, vec2d_round(tmp, true));
	return (tri);
}


void arrow_triangle_draw(t_img *minimap, t_vec2iv3 tri, t_color fill, t_border border)
{
	t_vec2iv3	outer;
	if (border.px)
	{
		outer = _grow_triangle(tri, border.px);
		ft_mlx_img_put_triangle(minimap, outer, border.color);
	}
	ft_mlx_img_put_triangle(minimap, tri, fill);
}
