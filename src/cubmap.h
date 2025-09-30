/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:22:06 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 14:49:30 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBMAP_H
# define CUBMAP_H

# include <stdint.h>

# include "color.h"
# include "data/sprite.h"
# include "door/door.h"
# include "ft_mlx/ft_mlx_texture.h"
# include "vec/vec.h"

typedef enum e_directions	t_directions;
typedef enum e_texture_id	t_texture_id;
typedef struct s_grid		t_grid;
typedef struct s_map		t_map;
typedef struct s_door		t_door;
typedef struct s_sprite		t_sprite;

enum e_directions
{
	DIR_N,
	DIR_S,
	DIR_E,
	DIR_W,
	DIR_MAX,
};

enum e_texture_id
{
	TEX_N = DIR_N,
	TEX_S = DIR_S,
	TEX_E = DIR_E,
	TEX_W = DIR_W,
	TEX_DOOR,
	TEX__COUNT
};

struct s_grid
{
	char	**grid;
	t_vec2i	dim;
};

struct s_map
{
	t_grid			g;
	t_texture		textures[TEX__COUNT];
	t_color			floor_colr;
	t_color			ceil_colr;
	t_door			**doors;
	t_sprites_data	bank;
};

void	free_map(t_map *m, t_mlx *mlx);
void	free_grid(t_grid *g);

#endif