/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 23:31:26 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/21 07:59:40 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "color.h"
#include "ft_mlx_img.h"
#include "loop/render/render.h"
#include "vec/ftmath_utils.h"
#include "vec/vec.h"
#include "data/data.h"

static inline void	_draw_arrow(t_img *minimap, const t_vec2i player,
	const t_vec2d dir_img_units, const t_arrow_len L)
{
	t_vec2d	n;
	t_vec2d	tmp;
	t_vec2i	base;
	t_vec2i	tip;
	t_vec2v	arrow_lr;

	n = (t_vec2d){-dir_img_units.y, dir_img_units.x};
	tmp = vec2d_scalar_mult(dir_img_units, L.arrow_depth);
	tip = vec2i_sum(player, vec2d_round(tmp, true));
	tmp = vec2d_scalar_mult(dir_img_units, L.head_len);
	base = vec2i_minus(tip, vec2d_round(tmp, true));
	tmp = vec2d_scalar_mult(n, L.head_wid);
	arrow_lr.a = vec2i_sum(base, vec2d_round(tmp, true));
	arrow_lr.b = vec2i_minus(base, vec2d_round(tmp, true));
	ft_mlx_img_put_line(minimap, tip, arrow_lr.a,
		(t_color){.value=C_PLAYER_DIR_ARROW});
	ft_mlx_img_put_line(minimap, tip, arrow_lr.b,
		(t_color){.value=C_PLAYER_DIR_ARROW});
}

static void	_draw_player_dir_arrow(t_img *minimap, const t_vec2d cam_dir,
	const t_vec2i player)
{
	t_vec2d		d;
	t_vec2d		u;
	t_arrow_len	L;
	double		norm;

	L.arrow_depth = MINIMAP_SCALE * MINIMAP_ARROW_DEPTH;
	L.head_wid = MINIMAP_SCALE * MINIMAP_ARROW_WIDTH;
	L.head_len = MINIMAP_SCALE * MINIMAP_ARROW_LEN;
	d.x = cam_dir.x;
	d.y = -cam_dir.y;
	norm = vec2d_get_norm(d);
	if (norm < 1e-9)
		return ;
	u = vec2d_scalar_mult(d, 1 / norm);
	_draw_arrow(minimap, player, u, L);
}

void	render_minimap_player(t_img *minimap, t_vec2i start, int32_t grid_height, const t_camera *cam)
{
	t_vec2i	player;
	t_vec2i	i;
	int32_t	r;

	player.x = (cam->pos.x - (double)start.x) * MINIMAP_SCALE;
	player.y =
		((double)grid_height - cam->pos.y - (double)start.y) * MINIMAP_SCALE;
	r = 1;
	if (MINIMAP_SCALE >= 4)
		r = MINIMAP_SCALE / 2.5;
	i.y = -r;
	while (i.y <= r)
	{
		i.x = -r;
		while (i.x <= r)
		{
			if (i.x * i.x + i.y * i.y <= r * r)
				ft_mlx_img_put_px(minimap, vec2i_sum(player, i), C_PLAYER);
			i.x++;
		}
		i.y++;
	}
	_draw_player_dir_arrow(minimap, cam->dir, player);
}
