/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 22:53:10 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/27 14:19:41 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "color.h"
#include "ft_mlx_img.h"
#include "vec/ftmath_utils.h"
#include "vec/vec.h"
#include "minimap.h"
#include "cubmap.h"

static inline void	_fill_one_square(t_img *img, t_vec2i square_pos,
	int32_t size, t_color color)
{
	t_vec2i	start_px;
	t_vec2i	end_px;

	start_px = vec2i_scalar_mult(square_pos, size);
	end_px.x = start_px.x + size;
	end_px.y = start_px.y + size;
	ft_mlx_img_put_square(img, start_px, end_px, color);
}

static inline t_color	_find_color(char cell)
{
	t_color	color;

	if (cell == '1')
		color.value = C_DARK_GRAY;
	else if (cell == '0')
		color.value = C_LIGHT_GRAY;
	else
		color.value = C_SPAWN;
	return (color);
}

static t_vec2i	_get_grid_start(t_vec2i minimap_dim, t_vec2i grid_dim,
	t_vec2d cam_pos, t_vec2i *tiles_displayed)
{
	t_vec2i	start;
	t_vec2i	max_start;
	t_vec2i	center;

	center.y = get_y_pos(grid_dim.y, cam_pos.y);
	center.x = (int32_t)floor(cam_pos.x);
	*tiles_displayed = vec2i_scalar_mult(
		minimap_dim,
		1.0 / (double)MINIMAP_SCALE
	);
	start = vec2i_minus(
		center, 
		vec2i_scalar_mult(*tiles_displayed, 0.5)
	);
	max_start = vec2i_minus(grid_dim, *tiles_displayed);
	if (max_start.x < 0)
		max_start.x = 0;
	if (max_start.y < 0)
		max_start.y = 0;
	return (vec2i_clamp(start, (t_vec2i){0}, max_start));
}

static void	_put_minimap_border(t_img *minimap, int32_t thick, t_color color)
{
	t_vec2i	top_l;
	t_vec2i	a;
	t_vec2i	b;

	if (thick <= 0)
		return ;
	top_l = (t_vec2i){0};
	a = top_l;
	b = (t_vec2i){minimap->dim.x, top_l.y + thick};
	ft_mlx_img_put_square(minimap, a, b, color);
	a = (t_vec2i){top_l.x, minimap->dim.y - thick};
	b = minimap->dim;
	ft_mlx_img_put_square(minimap, a, b, color);
	a = (t_vec2i){top_l.x, top_l.y + thick};
	b = (t_vec2i){top_l.x + thick, minimap->dim.y - thick};
	ft_mlx_img_put_square(minimap, a, b, color);
	a = (t_vec2i){minimap->dim.x - thick, top_l.y + thick};
	b = (t_vec2i){minimap->dim.x, minimap->dim.y - thick};
	ft_mlx_img_put_square(minimap, a, b, color);
}

void	render_minimap(t_img *minimap, const t_grid *grid, const t_camera *cam)
{
	t_vec2i	tiles_dim;
	t_vec2i	start;
	t_vec2i	i;
	t_vec2i	curr;

	start = _get_grid_start(minimap->dim, grid->dim, cam->pos, &tiles_dim);
	i.y = 0;
	while (i.y < tiles_dim.y)
	{
		curr.y = i.y + start.y;
		i.x = 0;
		while (i.x < tiles_dim.x)
		{
			curr.x = i.x + start.x;
			if (curr.x >= 0 && curr.y >= 0
				&& curr.x < grid->dim.x && curr.y < grid->dim.y)
				_fill_one_square(minimap, i, MINIMAP_SCALE,
					_find_color(grid->grid[curr.y][curr.x]));
			i.x++;
		}
		i.y++;
	}
	render_minimap_player(minimap, start, grid->dim.y, cam);
	_put_minimap_border(minimap, MINIMAP_BORDER_PX, (t_color){.value=MINIMAP_BORDER_COLOR});
}
