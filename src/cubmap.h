/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:22:06 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/10 11:54:15 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBMAP_H
# define CUBMAP_H

# include <stdint.h>

# include "vec.h"
# include "color.h"

enum e_directions
{
	DIR_N,
	DIR_S,
	DIR_E,
	DIR_W,
	DIR_MAX
};
typedef enum e_directions	t_directions;

struct s_player
{
	t_vec2d	pos;
	t_vec2d	dir;
	t_vec2d	plane;
};
typedef struct s_player	t_player;

struct s_map
{
	char		**grid;
	t_vec2i		dimensions;
	char		*tex_paths[DIR_MAX];
	t_color		*floor_colr;
	t_color		*ceil_colr;
	t_player	player;
};
typedef struct s_map	t_map;

void	free_map(t_map *m);

#endif