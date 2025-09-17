/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:15:16 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/17 17:47:05 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../data.h"
#include "loop/loop.h"
#include "vec/vec.h"
#include <stdint.h>

int16_t	install_mlx_img(t_mlx *mlx, t_img *img, t_vec2i screen_dim)
{
	img->image = mlx_new_image(mlx->display, screen_dim.x, screen_dim.y);
	if (!img->image)
		return (1);
	img->data_addr = (int8_t *)mlx_get_data_addr(img->image, 
		&img->bpp, &img->line_len, &img->endian);
	if (!img->data_addr)
		return (1);
	return (0);
}

int16_t	install_mlx(t_mlx *mlx, t_vec2i screen)
{
	mlx->display = mlx_init();
	if (!mlx->display)
		return (1);
	mlx->window = mlx_new_window(mlx->display,
		screen.x, screen.y, WIN_NAME);
	if (!mlx->window)
		return (1);
	if (install_mlx_img(mlx, &mlx->img, screen))
		return (1);
	mlx_do_key_autorepeatoff(mlx->display);
	return (0);
}

void	install_frame_engine(t_data *data)
{
	mlx_loop_hook(data->mlx.display, &app_loop_hook, data);
}
