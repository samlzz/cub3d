/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:32:16 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 02:18:24 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mlx.h"
#include "libft.h"
#include "data.h"
#include "cubmap.h"
#include "ft_mlx/ft_mlx_img.h"
#include "ft_mlx/ft_mlx_texture.h"
#include "parsing/parse_utils.h"
#include "sprite.h"

const t_sprite_meta	*sprites_get_metadata(size_t *count)
{
	static const t_sprite_meta sprites_def[] = {
		{
			.name = "Mewtwo",
			.paths = {
					"./assets/mewtwo/mewtwo000.xpm",
					"./assets/mewtwo/mewtwo001.xpm",
					"./assets/mewtwo/mewtwo002.xpm",
					"./assets/mewtwo/mewtwo003.xpm",
					"./assets/mewtwo/mewtwo004.xpm",
					"./assets/mewtwo/mewtwo005.xpm",
					"./assets/mewtwo/mewtwo006.xpm",
					NULL
			},
			.default_pos = { 36.5, 11.5 }
		},
	};
	*count = (sizeof (sprites_def) / sizeof (t_sprite_meta));
	return (sprites_def);
}

int16_t	sprite_load(t_sprite *dst, const char *const *paths, t_mlx *mlx)
{
	size_t		i;
	size_t		size;
	t_texture	tex;

	size = 0;
	while (paths[size])
		size++;
	dst->frames = ft_calloc(size, sizeof (t_img));
	if (!dst->frames)
		return (perror("cub3d: sprit_load: malloc"), 1);
	i = 0;
	while (i < size)
	{
		tex.path = (char *)paths[i];
		if (ft_mlx_texture_load(&tex, mlx))
		{
			dst->count = i;
			sprite_free(*dst, mlx);
			return (1);
		}
		dst->frames[i++] = tex.img;
	}
	dst->count = size;
	return (0);
}

void	sprite_free(t_sprite sprite, t_mlx *mlx)
{
	int32_t	i;
	void	*img_ptr;

	if (!sprite.frames || sprite.count <= 0)
		return ;
	i = 0;
	while (i < sprite.count)
	{
		img_ptr = sprite.frames[i].image_ptr;
		if (img_ptr)
			mlx_destroy_image(mlx->display, img_ptr);
		i++;
	}
	free(sprite.frames);
}

static bool	is_a_sprit_char(char c)
{
	return (c != '1' && !ft_is_walkable(c) && !ft_isspace(c));
}

int32_t	sprite_get_nb_in_map(const t_grid g)
{
	int32_t	sprite_nb;
	t_vec2i	index;

	index.y = 0;
	sprite_nb = 0;
	while (index.y < g.dim.y)
	{
		while (g.grid[index.y][index.x])
		{
			if (is_a_sprit_char(g.grid[index.y][index.x]))
				sprite_nb++;
			index.x++;
		}
		index.y++;
	}
	return (sprite_nb);
}
