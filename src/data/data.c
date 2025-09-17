/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:10:02 by eazard            #+#    #+#             */
/*   Updated: 2025/09/17 17:46:53 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "cubmap.h"
#include "mlx.h"
#include "data.h"
#include "vec/vec.h"

void	data_init(t_data *data)
{
	if (install_mlx(&data->mlx, (t_vec2i){WIN_WIDTH, WIN_HEIGHT}))
		clear_data(data, true, MLX_INIT_ERROR);
	install_hooks(data);
	install_frame_engine(data);
	camera_init(&data->camera, data->map.g);
}

static void	_fatal_clear_mlx(t_mlx *mlx)
{
	mlx_do_key_autorepeaton(mlx->display);
	if (mlx->display && mlx->img.image)
	{
		mlx_destroy_image(mlx->display,
			mlx->img.image);
		mlx->img.image = NULL;
	}
	if (mlx->display && mlx->window)
	{
		mlx_destroy_window(mlx->display,
			mlx->window);
		mlx->window = NULL;
	}
	if (mlx->display)
	{
		mlx_destroy_display(mlx->display);
		free(mlx->display);
		mlx->display = NULL;
	}
}

void	clear_data(t_data *data, bool fatal, int16_t exit_code)
{
	if (fatal)
		_fatal_clear_mlx(&data->mlx);
	free_map(&data->map);
	if (fatal)
		exit(exit_code);
}
