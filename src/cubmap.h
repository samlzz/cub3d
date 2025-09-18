/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:22:06 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/18 16:09:49 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBMAP_H
# define CUBMAP_H

# include <stdint.h>

# include "color.h"
# include "vec/vec.h"

typedef enum e_directions	t_directions;
typedef struct s_grid		t_grid;
typedef struct s_map		t_map;

enum e_directions
{
	DIR_N,
	DIR_S,
	DIR_E,
	DIR_W,
	DIR_MAX
};

struct s_grid
{
	char	**grid;
	t_vec2i	dim;
};

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