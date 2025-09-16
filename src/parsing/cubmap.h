/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:22:06 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/16 15:51:56 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBMAP_H
# define CUBMAP_H

# include <stdint.h>

# include "cub3d.h"
# include "color.h"

typedef enum e_directions	t_directions;
typedef struct s_map		t_map;
typedef struct s_player		t_player;
typedef union u_color		t_color;

enum e_directions
{
	DIR_N,
	DIR_S,
	DIR_E,
	DIR_W,
	DIR_MAX
};

struct s_player
{
	t_vec2d	pos;
	t_vec2d	dir;
	t_vec2d	plane;
};

struct s_grid
{
	char	**grid;
	t_vec2i	dim;
};
typedef struct s_grid t_grid;
struct s_map
{
	t_grid		g;
	char		*tex_paths[DIR_MAX];
	t_color		*floor_colr;
	t_color		*ceil_colr;
	// t_player	player;
};

void	free_map(t_map *m);

#endif