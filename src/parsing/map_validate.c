/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:29:02 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/29 16:35:15 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "parsing/fields.h"
#include "vec/vec.h"
#include "parse_utils.h"
#include "parse_err.h"
#include "cubmap.h"

static inline int16_t	_fill_norm_row(const char *row, int32_t tot_width,
	char **dest)
{
	int32_t	len;
	int32_t	inner_w;

	*dest = malloc((tot_width + 1) * sizeof (char));
	if (!*dest)
		return (perror("cub3d: get_normalized_grid: malloc"), 1);
	ft_memset(*dest, ' ', tot_width);
	(*dest)[tot_width] = '\0';
	if (!row)
		return (0);
	inner_w = tot_width - 2;
	len = (int32_t)ft_strlen(row);
	if (len > inner_w)
		len = inner_w;
	ft_memmove(*dest + 1, row, (size_t)len);
	return (0);
}

t_grid	*get_normalized_grid(const t_grid *usr_map)
{
	t_grid		*normalized;
	const char	*src;
	int32_t		y;

	normalized = ft_calloc(1, sizeof (t_grid));
	if (!normalized)
		return (perror("cub3d: get_normalized_grid: calloc"), NULL);
	normalized->dim = (t_vec2i){usr_map->dim.x + 2, usr_map->dim.y + 2};
	normalized->grid = ft_calloc(normalized->dim.y + 1, sizeof (char *));
	if (!normalized->grid)
		return (perror("cub3d: get_normalized_grid: calloc"),
			free(normalized), NULL);
	y = 0;
	while (y < normalized->dim.y)
	{
		if (y == 0 || y == normalized->dim.y - 1)
			src = NULL;
		else
			src = usr_map->grid[y - 1];
		if (_fill_norm_row(src, normalized->dim.x, normalized->grid + y))
			return (ft_splitfree(normalized->grid, (size_t)y), NULL);
		y++;
	}
	return (normalized);
}

static bool	_check_neighbors(const t_grid n, const t_vec2i pos)
{
	static const int32_t	DX[4] = { 1, -1,  0,  0 };
	static const int32_t	DY[4] = { 0,  0,  1, -1 };
	size_t					i;
	t_vec2i					curr;

	i = 0;
	while (i < 4)
	{
		curr.x = pos.x + DX[i];
		curr.y = pos.y + DY[i];
		if (curr.x >= 0 && curr.y >= 0 && curr.x < n.dim.x && curr.y < n.dim.y)
		{
			if (n.grid[curr.y][curr.x] == ' ')
				return (true);
		}
		i++;
	}
	return (false);
}

static inline t_parse_err	_check_pos(const t_grid *n, const t_vec2i *pos, 
	bool *has_walkable, int32_t *usr_occ)
{
	char	v;

	v = n->grid[pos->y][pos->x];
	if (!ft_is_walkable(v))
		return (PE_OK);
	*has_walkable = true;
	if (v != '0' && v != 'D')
		(*usr_occ)++;
	if (*usr_occ > 1)
		return (PE_U_MAP_PLAYER_MANY);
	if (_check_neighbors(*n, *pos))
		return (PE_U_MAP_OPEN);
	return (0);
}

t_parse_err	validate_map_closed(const t_grid *normalized, int32_t *y_err)
{
	const t_grid	*n;
	t_vec2i			i;
	int32_t			usr_occurences;
	bool			has_walkable;
	t_parse_err		code;

	n = normalized;
	i.y = 1;
	has_walkable = false;
	usr_occurences = 0;
	while (i.y < n->dim.y - 1)
	{
		i.x = 1;
		while (i.x < n->dim.x - 1)
		{
			code = _check_pos(n, &i, &has_walkable, &usr_occurences);
			if (code)
				return (*y_err = i.y - 1, code);
			i.x++;
		}
		i.y++;
	}
	if (!usr_occurences)
		return (*y_err = i.y - 1, PE_U_MAP_PLAYER_MISSING);
	return (*y_err = i.y - 1, PE_U_MAP_NO_WALKABLE * !has_walkable);
}
