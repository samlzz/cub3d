/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:33:52 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 15:43:10 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_mlx/ft_mlx_img.h"
#include "loop/loop.h"
#include "minimap.h"
#include "vec/vec.h"

static void	_draw_player_dir_triangle(t_img *minimap, const t_vec2d cam_dir,
	const t_vec2i player)
{
	t_vec2d		d;
	t_vec2d		u;
	t_arrow_len	len;
	double		norm;
	t_vec2iv3	tri;

	len.arrow_depth = MINIMAP_SCALE * MINIMAP_ARROW_DEPTH;
	len.head_wid = MINIMAP_SCALE * MINIMAP_ARROW_WIDTH;
	len.head_len = MINIMAP_SCALE * MINIMAP_ARROW_LEN;
	d.x = cam_dir.x;
	d.y = -cam_dir.y;
	norm = vec2d_get_norm(d);
	if (norm < EPS)
		return ;
	u.x = d.x / norm;
	u.y = d.y / norm;
	tri = arrow_triangle_build(player, u, len);
	arrow_triangle_draw(
		minimap,
		tri,
		(t_color){.value = C_BLACK},
		(t_border){MINIMAP_ARROW_BORDER, (t_color){.value = C_WHITE}}
		);
}

void	render_minimap_player(t_img *minimap, t_vec2i start, int32_t grid_h,
	const t_camera *cam)
{
	t_vec2i	player;
	int32_t	diam;

	player.x = (cam->pos.x - (double)start.x) * MINIMAP_SCALE;
	player.y = ((double)grid_h - cam->pos.y - (double)start.y) * MINIMAP_SCALE;
	if (MINIMAP_SCALE >= 4)
		diam = MINIMAP_SCALE;
	else
		diam = 1;
	ft_mlx_img_put_sphere(minimap, player, diam,
		(t_color){.value = C_PLAYER});
	_draw_player_dir_triangle(minimap, cam->dir, player);
}
