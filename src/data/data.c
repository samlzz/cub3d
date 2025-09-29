/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:10:02 by eazard            #+#    #+#             */
/*   Updated: 2025/09/28 19:36:33 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

#include "ft_mlx/ft_mlx_texture.h"
#include "libft.h"
#include "cubmap.h"
#include "mlx.h"
#include "data.h"
#include "vec/vec.h"

void	data_init(t_data *data)
{
	if (install_mlx(
		&data->mlx,
		(t_vec2i){WIN_WIDTH, WIN_HEIGHT},
		&data->inputs.cursor,
		data->map.g.dim
	))
		data_exit(data, EC_MLX_INIT_ERROR);
	if (ft_mlx_textures_load_list(data->map.textures, DIR_MAX, &data->mlx))
		data_exit(data, EC_OPEN_TEXTURE_FAILURE);
	install_hooks(data);
	install_frame_engine(data);
	camera_init(&data->camera, data->map.g);
}

static void	_fatal_clear_mlx(t_mlx *mlx)
{
	mlx_do_key_autorepeaton(mlx->display);
	if (mlx->display && mlx->game.image_ptr)
		mlx_destroy_image(mlx->display, mlx->game.image_ptr);
	if (mlx->minimap.image_ptr)
		mlx_destroy_image(mlx->display, mlx->minimap.image_ptr);
	if (mlx->window)
		mlx_destroy_window(mlx->display,
			mlx->window);
	mlx_destroy_display(mlx->display);
	free(mlx->display);
	ft_bzero(mlx, sizeof (t_mlx));
}

void	data_exit(t_data *data, t_init_error code)
{
	free_map(&data->map, &data->mlx);
	_fatal_clear_mlx(&data->mlx);
	// todo: handle err message depends on code
	exit(code);
}
