/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:54:21 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 15:59:02 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "mlx.h"
#include "data/data.h"
#include "parsing/parse_err.h"
#include "ft_mlx_texture.h"

static inline bool	_file_found_and_readable_(char *path)
{
	int	fd;

	if (!path)
		return (1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (open_err(path), false);
	return (close(fd), true);
}

int16_t	ft_mlx_texture_load(t_texture *tex, t_mlx *mlx)
{
	t_img	img;

	if (!tex)
		return (2);
	if (!_file_found_and_readable_(tex->path))
		return (1);
	img.image_ptr = mlx_xpm_file_to_image(
			mlx->display,
			tex->path,
			&img.dim.x, &img.dim.y);
	if (!img.image_ptr)
		return (1);
	img.data_addr = mlx_get_data_addr(
			img.image_ptr,
			&img.bpp, &img.line_len, &img.endian
			);
	tex->img = img;
	return (0);
}

void	ft_mlx_texture_destroy(t_texture *tex, t_mlx *mlx)
{
	free(tex->path);
	if (tex->img.image_ptr)
		mlx_destroy_image(mlx->display, tex->img.image_ptr);
}

int16_t	ft_mlx_textures_load_list(t_texture *list, int32_t count, t_mlx *mlx)
{
	int32_t	i;
	int32_t	j;

	i = 0;
	while (i < count)
	{
		if (ft_mlx_texture_load(list + i, mlx))
		{
			j = 0;
			while (j < i)
				ft_mlx_texture_destroy(list + j++, mlx);
			return (1);
		}
		i++;
	}
	return (0);
}
