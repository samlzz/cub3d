/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   install_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:22:56 by eazard            #+#    #+#             */
/*   Updated: 2025/09/18 09:12:26 by eazard           ###   ########.fr       */
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
	data->mlx.img.image_ptr = mlx_new_image(data->mlx.display,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->mlx.img.image_ptr == NULL)
		clear_data(data, true, MLX_INIT_ERROR);
	data->mlx.img.data_addr = mlx_get_data_addr(data->mlx.img.image_ptr,
			&data->mlx.img.bpp, &data->mlx.img.line_len,
			&data->mlx.img.endian);
	fprintf(stderr, "endian = %i \nbpp= %i\n line_len = %i \n", data->mlx.img.endian, data->mlx.img.bpp, data->mlx.img.line_len);
	fflush(stderr);
}

void	install_mlx(t_data *data)
{
	init_mlx_display(data);
	init_mlx_window(data);
	init_mlx_image(data);
	mlx_do_key_autorepeatoff(data->mlx.display);
}
