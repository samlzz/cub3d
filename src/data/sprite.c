/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:32:16 by sliziard          #+#    #+#             */
/*   Updated: 2025/10/01 10:50:53 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef CUB3D_BONUS

# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

# include "mlx.h"
# include "libft.h"
# include "data.h"
# include "cubmap.h"
# include "ft_mlx/ft_mlx_img.h"
# include "ft_mlx/ft_mlx_texture.h"
# include "parsing/parse_utils.h"
# include "sprite.h"

# define MT_1	"./assets/mewtwo/mewtwo000.xpm"
# define MT_2	"./assets/mewtwo/mewtwo001.xpm"
# define MT_3	"./assets/mewtwo/mewtwo002.xpm"
# define MT_4	"./assets/mewtwo/mewtwo003.xpm"
# define MT_5	"./assets/mewtwo/mewtwo004.xpm"
# define MT_6	"./assets/mewtwo/mewtwo005.xpm"
# define MT_7	"./assets/mewtwo/mewtwo006.xpm"

# define QB_1	"./assets/culbutoke/culbutoke0.xpm"
# define QB_2	"./assets/culbutoke/culbutoke1.xpm"
# define QB_3	"./assets/culbutoke/culbutoke2.xpm"
# define QB_4	"./assets/culbutoke/culbutoke3.xpm"
# define QB_5	"./assets/culbutoke/culbutoke4.xpm"

# define LG_1	"./assets/lugia/lugia0.xpm"
# define LG_2	"./assets/lugia/lugia1.xpm"

# define OO_1	"./assets/oh_oh/oh_oh0.xpm"
# define OO_2	"./assets/oh_oh/oh_oh1.xpm"

const t_sprite_meta	*sprites_get_metadata(size_t *count)
{
	static const t_sprite_meta	sprites_def[] = {
	{
		.name = "Mewtwo 1",
		.paths = {MT_1, MT_2, MT_3, MT_4, MT_5, MT_6, MT_7, NULL},
		.default_pos = {36.5, 11.5}
	},
	{
		.name = "Mewtwo 2",
		.paths = {MT_1, MT_2, MT_3, MT_4, MT_5, MT_6, MT_7, NULL},
		.default_pos = {-200, -100}
	},
	{
		.name = "culbutoke", .paths = {QB_1, QB_2, QB_3, QB_4, QB_5},
		.default_pos = {36.5, 10.5}
	},
	{
		.name = "lugia", .paths = {LG_1, LG_2}, .default_pos = {36.5, 8.5}
	},
	{
		.name = "oh oh", .paths = {OO_1, OO_2}, .default_pos = {36.5, 13.5}
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

	if (!sprite.frames || sprite.count < 0)
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

#endif
