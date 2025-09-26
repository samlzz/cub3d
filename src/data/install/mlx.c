/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:15:16 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/26 22:25:01 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "mlx.h"
#include "../data.h"
#include "loop/loop.h"
#include "vec/ftmath_utils.h"
#include "vec/vec.h"
#include "loop/render/minimap.h"

int16_t	install_mlx_img(t_mlx *mlx, t_img *img, t_vec2i img_dim)
{
	img->image_ptr = mlx_new_image(mlx->display, img_dim.x, img_dim.y);
	if (!img->image_ptr)
		return (1);
	img->data_addr = mlx_get_data_addr(img->image_ptr,
		&img->bpp, &img->line_len, &img->endian);
	img->dim = img_dim;
	if (!img->data_addr)
		return (1);
	return (0);
}

static inline t_vec2i	_get_minimap_dim(t_vec2i grid_dim)
{
	t_vec2i	dim;
	int32_t	rad_dim;

	rad_dim = MINIMAP_RADIUS * 2 + 1;
	dim.x = ftm_min(rad_dim, grid_dim.x);
	dim.y = ftm_min(rad_dim, grid_dim.y);
	return (vec2i_scalar_mult(dim, MINIMAP_SCALE));
}

int16_t	install_mlx(t_mlx *mlx, t_vec2i screen, t_vec2i grid)
{
	t_vec2i	dim;

	mlx->display = mlx_init();
	if (!mlx->display)
		return (1);
	mlx->window = mlx_new_window(mlx->display,
		screen.x, screen.y, WIN_NAME);
	if (!mlx->window)
		return (1);
	if (install_mlx_img(mlx, &mlx->game, screen))
		return (1);
	dim = _get_minimap_dim(grid);
	if (install_mlx_img(mlx, &mlx->minimap, dim))
		return (1);
	mlx->minimap_pos.y = 0;
	mlx->minimap_pos.x = WIN_WIDTH - dim.x;
	mlx_do_key_autorepeatoff(mlx->display);
	return (0);
}

void	install_frame_engine(t_data *data)
{
	mlx_loop_hook(data->mlx.display, &app_loop_hook, data);
}
