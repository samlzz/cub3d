/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:22:06 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/29 15:27:47 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBMAP_H
# define CUBMAP_H

# define DOOR_PATH "./assets/texture/DOOM/door/green_organic.xpm"

# include <stdint.h>

# include "color.h"
# include "vec/vec.h"
# include "door/door.h"
# include "animated_asset/animated_asset.h"

typedef enum e_directions	t_directions;
typedef struct s_grid		t_grid;
typedef struct s_map		t_map;
typedef struct s_door		t_door;

enum e_directions
{
	DIR_N,
	DIR_S,
	DIR_E,
	DIR_W,
	DIR_MAX,
};

struct s_grid
{
	char	**grid;
	t_vec2i	dim;
};

struct s_map
{
	t_grid		g;
	t_door		**doors;
	char		*tex_paths[DIR_MAX];
	t_color		*floor_colr;
	t_color		*ceil_colr;
	t_sprite	sprites[SPRITE_NB];
	int			sprite_order[SPRITE_NB];
	double		sprite_distance_square[SPRITE_NB];
}

void	free_map(t_map *m);

#endif