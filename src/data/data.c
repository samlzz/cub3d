/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:10:02 by eazard            #+#    #+#             */
/*   Updated: 2025/09/27 15:47:27 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "cubmap.h"
#include "mlx.h"
#include "data.h"
#include "vec/vec.h"
#include "door/door.h"

void	data_init(t_data *data)
{
	if (install_mlx(&data->mlx, (t_vec2i){WIN_WIDTH, WIN_HEIGHT}))
		clear_data(data, true, EC_MLX_INIT_ERROR);
	if (load_cardinal_textures(&data->map, data->assets.cardinal_textures,
			&data->mlx))
		clear_data(data, true, EC_OPEN_TEXTURE_FAILURE);
	if (load_door_texture(&data->assets.door,
		&data->mlx))
		clear_data(data, true, EC_OPEN_TEXTURE_FAILURE);
	if (install_doors(&data->map.g, &data->map.doors))
		clear_data(data, true, EC_INSTALLING_DOOR_FAILURE);
	install_hooks(data);
	install_frame_engine(data);
	camera_init(&data->camera, data->map.g);
}

static void	_fatal_clear_mlx(t_mlx *mlx)
{
	mlx_do_key_autorepeaton(mlx->display);
	if (mlx->display && mlx->img.image_ptr)
	{
		mlx_destroy_image(mlx->display,
			mlx->img.image_ptr);
		mlx->img.image_ptr = NULL;
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
		fatal_clear_cardinal_textures(&data->mlx,
			data->assets.cardinal_textures);
	if (fatal)
		fatal_clear_door_texture(&data->mlx, &data->assets.door);
	if (fatal)
		_fatal_clear_mlx(&data->mlx);
	if (fatal)
		free_map(&data->map);
	if (fatal)
		exit(exit_code);
}
