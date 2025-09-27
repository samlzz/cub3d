/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:36:33 by eazard            #+#    #+#             */
/*   Updated: 2025/09/27 15:48:19 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "mlx.h"
#include "cubmap.h"
#include "data.h"

int16_t	load_door_texture(t_img *door_texture,
		t_mlx *mlx)
{
	if (file_found_and_readable(DOOR_PATH) == false)
		return (EC_OPEN_TEXTURE_FAILURE);
	*door_texture
		= open_xpm_and_get_its_data(DOOR_PATH, mlx);
	if (door_texture->image_ptr == NULL)
		return (EC_OPEN_TEXTURE_FAILURE);
	return (EC_SUCCESS);
}

void	fatal_clear_door_texture(t_mlx *mlx, t_img *door_texture)
{
	if (door_texture->image_ptr != NULL)
	{
		mlx_destroy_image(mlx->display, door_texture->image_ptr);
		door_texture->image_ptr = NULL;
	}
}
