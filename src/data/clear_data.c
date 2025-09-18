/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:10:02 by eazard            #+#    #+#             */
/*   Updated: 2025/09/18 09:20:09 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

static void	clear_mlx(t_data *data, bool fatal)
{
	if (fatal)
	{
		mlx_do_key_autorepeaton(data->mlx.display);
		if (data->mlx.display && data->mlx.img.image_ptr)
		{
			mlx_destroy_image(data->mlx.display,
				data->mlx.img.image_ptr);
			data->mlx.img.image_ptr = NULL;
		}
		if (data->mlx.display && data->mlx.window)
		{
			mlx_destroy_window(data->mlx.display,
				data->mlx.window);
			data->mlx.window = NULL;
		}
		if (data->mlx.display)
		{
			mlx_destroy_display(data->mlx.display);
			free(data->mlx.display);
			data->mlx.display = NULL;
		}
	}
}

void	clear_cardinal_textures(t_mlx *mlx, t_img cardinal_textures[],
			bool fatal)
{
	int	i;

	if (fatal)
	{
		i = 0;
		while (i < DIR_MAX && cardinal_textures[i].image_ptr != NULL)
		{
			mlx_destroy_image(mlx->display, cardinal_textures[i].image_ptr);
			cardinal_textures[i].image_ptr = NULL;
			i++;
		}
	}
}

void	clear_data(t_data *data, bool fatal, int16_t exit_code)
{
	clear_cardinal_textures(&data->mlx, data->assets.cardinal_textures,
		fatal);
	clear_mlx(data, fatal);
	if (fatal)
		exit(exit_code);
}
