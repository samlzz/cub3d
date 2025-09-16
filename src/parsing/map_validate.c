/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:29:02 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/16 14:55:34 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "vec.h"
#include "parser.h"
#include "parse_utils.h"

static inline int16_t	_fill_norm_row(const char *row, int32_t tot_width,
	char **dest)
{
	int32_t	len;
	int32_t	inner_w;

	*dest = malloc((tot_width + 1) * sizeof (char));
	if (!*dest)
		return (1);
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
		return (NULL);
	normalized->dim = (t_vec2i){usr_map->dim.x + 2, usr_map->dim.y + 2};
	normalized->grid = ft_calloc(normalized->dim.y + 1, sizeof (char *));
	if (!normalized->grid)
		return (free(normalized), NULL);
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
			if (n.grid[pos.y][pos.x] == ' ')
				return (true);
		}
		i++;
	}
	return (false);
}

static inline int16_t	_check_pos(const t_grid *n, const t_vec2i *pos, 
	bool *has_walbkable, int32_t *usr_occ)
{
	char	v;

	v = n->grid[pos->y][pos->x];
	if (!ft_is_walkable(v))
		return (0);
	*has_walbkable = true;
	if (v != '0')
		(*usr_occ)++;
	if (*usr_occ > 1)
		return (2);
	if (_check_neighbors(*n, *pos))
		return (3);
	return (0);
}

int16_t	validate_map_closed(const t_grid *usr_map)
{
	t_grid	*n;
	t_vec2i	i;
	int32_t	usr_occurences;
	bool	has_walbkable;
	int16_t	code;

	n = get_normalized_grid(usr_map);
	if (!n)
		return (1);
	i.y = 1;
	has_walbkable = false;
	usr_occurences = 0;
	while (i.y < n->dim.y - 1)
	{
		i.x = 1;
		while (i.x < n->dim.x - 1)
		{
			code = _check_pos(n, &i, &has_walbkable, &usr_occurences);
			if (code)
				return (free_grid(n), free(n), code);
			i.x++;
		}
		i.y++;
	}
	return (free_grid(n), free(n), (2 * (!has_walbkable || !usr_occurences)));
}
