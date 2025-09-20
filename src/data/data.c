/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:10:02 by eazard            #+#    #+#             */
/*   Updated: 2025/09/19 17:24:51 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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
		data->map.g.dim)
	)
		clear_data(data, true, EC_MLX_INIT_ERROR);
	if (load_cardinal_textures(
		&data->map,
		data->assets.cardinal_textures,
		&data->mlx)
	)
		clear_data(data, true, EC_OPEN_TEXTURE_FAILURE);
	install_hooks(data);
	install_frame_engine(data);
	camera_init(&data->camera, data->map.g);
}

static void	_fatal_clear_mlx(t_mlx *mlx)
{
	mlx_do_key_autorepeaton(mlx->display);
	if (!mlx->display)
		return ;
	if (mlx->game.image_ptr)
		mlx_destroy_image(mlx->display,
			mlx->game.image_ptr);
	if (mlx->minimap.image_ptr)
		mlx_destroy_image(mlx->display, mlx->minimap.image_ptr);
	if (mlx->window)
		mlx_destroy_window(mlx->display,
			mlx->window);
	mlx_destroy_display(mlx->display);
	free(mlx->display);
	ft_bzero(mlx, sizeof (t_mlx));
}

void	clear_data(t_data *data, bool fatal, int16_t exit_code)
{
	if (fatal)
		fatal_clear_cardinal_textures(&data->mlx,
			data->assets.cardinal_textures);
	if (fatal)
		_fatal_clear_mlx(&data->mlx);
	free_map(&data->map);
	if (fatal)
		exit(exit_code);
}
