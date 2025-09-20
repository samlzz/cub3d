/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinal_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:29:34 by eazard            #+#    #+#             */
/*   Updated: 2025/09/19 17:16:39 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "error.h"
#include "mlx.h"
#include "cubmap.h"
#include "data.h"

bool	_file_found_and_readable_(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (open_err(path), false);
	return (close(fd), true);
}

t_img	open_xpm_and_get_its_data(char *path, t_mlx *mlx)
{
	t_img	img;

	img.image_ptr = mlx_xpm_file_to_image(mlx->display, path, &img.dim.x,
			&img.dim.y);
	if (img.image_ptr == NULL)
		return (open_err(path), img);
	img.data_addr = mlx_get_data_addr(img.image_ptr, &img.bpp, &img.line_len,
			&img.endian);
	return (img);
}

int16_t	load_cardinal_textures(t_map *map, t_img cardinal_textures[],
		t_mlx *mlx)
{
	int		i;

	i = 0;
	while (i < DIR_MAX)
	{
		if (_file_found_and_readable_(map->tex_paths[i]) == false)
			return (EC_OPEN_TEXTURE_FAILURE);
		cardinal_textures[i]
			= open_xpm_and_get_its_data(map->tex_paths[i], mlx);
		if (cardinal_textures[i].image_ptr == NULL)
			return (EC_OPEN_TEXTURE_FAILURE);
		i++;
	}
	return (EC_SUCCESS);
}

void	fatal_clear_cardinal_textures(t_mlx *mlx, t_img cardinal_textures[])
{
	int	i;

	i = 0;
	while (i < DIR_MAX && cardinal_textures[i].image_ptr != NULL)
	{
		mlx_destroy_image(mlx->display, cardinal_textures[i].image_ptr);
		cardinal_textures[i].image_ptr = NULL;
		i++;
	}
}
