/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:10:02 by eazard            #+#    #+#             */
/*   Updated: 2025/09/08 14:41:17 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

static void	clear_mlx(t_data *data, bool fatal)
{
	if (fatal)
	{
		if (data->mlx.display && data->mlx.img.image)
		{
			mlx_destroy_image(data->mlx.display,
				data->mlx.img.image);
			data->mlx.img.image = NULL;
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

void	clear_data(t_data *data, bool fatal, int16_t exit_code)
{
	clear_mlx(data, fatal);
	if (fatal)
		exit(exit_code);
}
