/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:39:11 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/14 18:39:19 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "cubmap.h"
#include "ft_lifo.h"
#include "libft.h"
#include "vec.h"
#include "parser.h"
#include "parse_utils.h"

static inline int32_t	get_id(int32_t W, int32_t x, int32_t y)
{
	return (y * W + x);
}

static inline void	get_coor(int32_t W, int32_t id, t_vec2i *coor)
{
	coor->x = id % W;
	coor->y = id / W;
}

static bool	_check_neighbors(char **n, t_vec2i n_dim, const t_vec2i space, t_lifo *st)
{
	static const int32_t	DX[4] = { 1, -1,  0,  0 };
	static const int32_t	DY[4] = { 0,  0,  1, -1 };
	size_t					i;
	t_vec2i					curr;
	char					v;

	i = 0;
	while (i < 4)
	{
		curr.x = space.x + DX[i];
		curr.y = space.y + DY[i];
		if (curr.x >= 0 && curr.y >= 0 && curr.x < n_dim.x && curr.y < n_dim.y)
		{
			v = n[curr.y][curr.x];
			if (ft_is_walkable(v))
				return (true);
			if (v == ' ')
			{
				n[curr.y][curr.x] = '$';
				ft_lifo_push(st, get_id(n_dim.x, curr.x, curr.y));
			}
		}
		i++;
	}
	return (false);
}

/**
	Flood by outside, DFS itératif

	Start at (0, 0)
*/
int16_t	validate_map_closed(const t_map *m)
{
	char	**n;
	t_vec2i	ndim;
	int32_t	curr_val;
	t_vec2i	curr_vec;
	t_lifo	st;

	n = get_normalized_grid(m, &ndim);
	if (!n)
		return (1);
	if (ft_lifo_init(&st, ndim.x * ndim.y))
		return (ft_splitfree(n, ndim.y), 1);
	ft_lifo_push(&st, 0);
	n[0][0] = '$';
	while (!ft_lifo_pop(&st, &curr_val))
	{
		get_coor(ndim.x, curr_val, &curr_vec);
		if (_check_neighbors(n, ndim, curr_vec, &st))
		{
			ft_splitfree(n, ndim.y);
			return (free(st.data), 3);
		}
	}
	ft_splitfree(n, ndim.y);
	return (free(st.data), 0);
}

/**
	Open file at `map_path` and fill `out`

	Return:
		0: exit successfully
		1: internal error (malloc fail, ...)
		2: user error
		3: map open
*/
int16_t	parse_cub(const char *map_path, t_map *out)
{
	int16_t	code;
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (1);
	code = parse_identifiers(fd, out);
	if (code)
		return (close(fd), code);
	code = parse_grid(fd, out);
	close(fd);
	if (code)
		return (code);
	code = validate_map_closed(out);
	if (code)
		return (code);
	return (0);
}

bool	is_dot_cub(const char *path)
{
	char	*dot;

	dot = ft_strrchr(path, '.');
	if (!dot)
		return (false);
	return (!ft_strcmp(dot + 1, "cub"));
}
