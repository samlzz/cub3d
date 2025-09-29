/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:54:21 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/29 15:52:48 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
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
	t_img	*new;

	if (!tex)
		return (2);
	if (!_file_found_and_readable_(tex->path))
		return (1);
	new = ft_calloc(1, sizeof (t_img));
	if (!new)
		return (1);
	new->image_ptr = mlx_xpm_file_to_image(
		mlx->display,
		tex->path,
		&new->dim.x, &new->dim.y);
	if (!new->image_ptr)
		return (free(new), 1);
	new->data_addr = mlx_get_data_addr(
		new->image_ptr,
		&new->bpp, &new->line_len, &new->endian
	);
	tex->img = new;
	return (0);
}

void	ft_mlx_texture_destroy(t_texture *tex, t_mlx *mlx)
{
	free(tex->path);
	if (tex->img)
		mlx_destroy_image(mlx->display, tex->img->image_ptr);
	free(tex->img);
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
