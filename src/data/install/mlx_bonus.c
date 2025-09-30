/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:15:16 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 17:04:43 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef CUB3D_BONUS

# include <stdint.h>

# include "mlx.h"
# include "../data.h"
# include "vec/ftmath_utils.h"
# include "vec/vec.h"
# include "loop/render/minimap.h"

void	install_mouse(t_mlx *mlx, t_mouse *cursor)
{
	mlx_mouse_hide(mlx->display, mlx->window);
	cursor->hidden = true;
	cursor->pos = (t_vec2i){WIN_WIDTH / 2, WIN_HEIGHT / 2};
	cursor->pending_recenter = true;
	mlx_mouse_move(mlx->display, mlx->window, cursor->pos.x, cursor->pos.y);
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

int16_t	install_mlx(t_mlx *mlx, t_vec2i screen, t_mouse *cursor, t_vec2i grid)
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
	install_mouse(mlx, cursor);
	return (0);
}

#endif
