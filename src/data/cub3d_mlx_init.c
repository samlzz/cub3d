/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_mlx_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:22:56 by eazard            #+#    #+#             */
/*   Updated: 2025/09/08 14:45:12 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

static void	init_mlx_window(t_data *data)
{
	data->mlx.window = mlx_new_window(data->mlx.display,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (data->mlx.window == NULL)
		clear_data(data, true, MLX_INIT_ERROR);
}

static void	init_mlx_display(t_data *data)
{
	data->mlx.display = mlx_init();
	if (data->mlx.display == NULL)
		clear_data(data, true, MLX_INIT_ERROR);
}

static void	init_mlx_image(t_data *data)
{
	data->mlx.img.image = mlx_new_image(data->mlx.display,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->mlx.img.image == NULL)
		clear_data(data, true, MLX_INIT_ERROR);
	data->mlx.img.data_addr = mlx_get_data_addr(data->mlx.img.image,
			&data->mlx.img.bpp, &data->mlx.img.line_len,
			&data->mlx.img.endian);
}

void	cub3d_mlx_init(t_data *data)
{
	init_mlx_display(data);
	init_mlx_window(data);
	init_mlx_image(data);
}