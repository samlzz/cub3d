/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:33:52 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/25 18:08:56 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "color.h"
#include "data/data.h"
#include "ft_mlx_img.h"
#include "minimap.h"
#include "vec/vec.h"

static void	_draw_player_dir_triangle(t_img *minimap, const t_vec2d cam_dir,
	const t_vec2i player)
{
	t_vec2d		d;
	t_vec2d		u;
	t_arrow_len	L;
	double		norm;
	t_vec2iv3	tri;

	L.arrow_depth = MINIMAP_SCALE * MINIMAP_ARROW_DEPTH;
	L.head_wid = MINIMAP_SCALE * MINIMAP_ARROW_WIDTH;
	L.head_len = MINIMAP_SCALE * MINIMAP_ARROW_LEN;
	d.x = cam_dir.x;
	d.y = -cam_dir.y;
	norm = vec2d_get_norm(d);
	if (norm < LITTLE)
		return ;
	u.x = d.x / norm;
	u.y = d.y / norm;
	tri = arrow_triangle_build(player, u, L);
	arrow_triangle_draw(
		minimap,
		tri,
		(t_color){ .value = C_BLACK },
		(t_border){MINIMAP_ARROW_BORDER,(t_color){.value = C_WHITE}}
	);
}

void	render_minimap_player(t_img *minimap, t_vec2i start, int32_t grid_h,
	const t_camera *cam)
{
	t_vec2i	player;
	int32_t	diam;

	player.x = (cam->pos.x - (double)start.x) * MINIMAP_SCALE;
	player.y = ((double)grid_h - cam->pos.y - (double)start.y) * MINIMAP_SCALE;

	diam = (MINIMAP_SCALE >= 4) ? MINIMAP_SCALE : 1;
	ft_mlx_img_put_sphere(minimap, player, diam, (t_color){ .value = C_PLAYER });
	_draw_player_dir_triangle(minimap, cam->dir, player);
}
