/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:26:45 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 16:39:31 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include <stddef.h>

# include "ft_mlx/ft_mlx_img.h"
# include "vec/vec.h"

# ifndef SPR_MAX_FRAMES
#  define SPR_MAX_FRAMES 32
# endif

typedef struct s_mlx			t_mlx;
typedef struct s_grid			t_grid;

typedef struct s_sprite_meta	t_sprite_meta;
typedef struct s_sprite			t_sprite;
typedef struct s_sprites_data	t_sprites_data;

struct s_sprite_meta
{
	char		marker;
	const char	*name;
	const char	*paths[SPR_MAX_FRAMES];
	t_vec2d		default_pos;
};

struct s_sprite
{
	t_img		*frames;
	int32_t		count;
	t_vec2d		pos;
	const char	*name;
};

struct s_sprites_data
{
	t_sprite	*sprites;
	int32_t		*order;
	double		*square_distances;
	size_t		count;
};

const t_sprite_meta	*sprites_get_metadata(size_t *count);

int16_t				sprite_load(t_sprite *dst, const char *const *paths,
						t_mlx *mlx);
void				sprite_free(t_sprite sprite, t_mlx *mlx);

/* Install */
int16_t				install_sprites_bank(t_sprites_data *bank, t_mlx *mlx);
void				clear_sprite_bank(t_sprites_data *bank, t_mlx *mlx);

#endif
