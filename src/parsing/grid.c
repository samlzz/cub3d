/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:29:49 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/13 12:12:26 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "cubmap.h"
#include "parse_utils.h"
#include "ft_gnl.h"
#include "libft.h"
#include "str_lst.h"
#include "vec.h"

#define MAP_BEGIN 0
#define SEEN_TRAILING_BLANK 1

static t_strlst	*_retrieve_nested_lines(int fd, int32_t	*size)
{
	char		*line;
	t_strlst	*head;
	bool		flags[2];

	head = NULL;
	ft_bzero(flags, 2 * sizeof (bool));
	while (ft_getline(&line, fd) > 0)
	{
		if (!line)
			return (strlst_clear(head), NULL);
		if (ft_isln_empty(line))
		{
			if (flags[MAP_BEGIN])
				flags[SEEN_TRAILING_BLANK] = true;
			free(line);
			continue ;
		}
		if (flags[SEEN_TRAILING_BLANK])
			return (strlst_clear(head), free(line), *size = -2, NULL);
		flags[MAP_BEGIN] = true;
		if (strlst_add_node(&head, line, size))
			return (strlst_clear(head), free(line), NULL);
	}
	return (head);
}

static inline void	_fill_grid(t_map *m, t_strlst *rows)
{
	int32_t	i;
	char	*ln;

	i = 0;
	m->dimensions.x = INT_MIN;
	while (i < m->dimensions.y && rows)
	{
		m->grid[i++] = rows->str;
		if (rows->str)
		{
			if (rows->len > m->dimensions.x)
				m->dimensions.x = rows->len;
			ln = ft_strrchr(rows->str, '\n');
			if (ln)
				*ln = '\0';
			rows->str = NULL;
		}
		rows = rows->next;
	}
}

int16_t	parse_grid(int fd, t_map *m)
{
	t_strlst	*head;

	head = _retrieve_nested_lines(fd, &m->dimensions.y);
	if (!head)
		return (1 + (m->dimensions.y == -2));
	m->grid = ft_calloc(m->dimensions.y + 1, sizeof (char *));
	if (!m->grid)
		return (strlst_clear(head), 1);
	_fill_grid(m, head);
	strlst_clear(head);
	return (0);
}

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

char	**get_normalized_grid(const t_map *m)
{
	t_vec2i		total;
	char		**normalized;
	const char	*src;
	int32_t		y;

	total = (t_vec2i){m->dimensions.x + 1, m->dimensions.y + 2};
	normalized = ft_calloc(total.y + 1, sizeof (char *));
	if (!normalized)
		return (NULL);
	y = 0;
	while (y < total.y)
	{
		if (y == 0 || y == total.y - 1)
			src = NULL;
		else
			src = m->grid[y - 1];
		if (_fill_norm_row(src, total.x, normalized + y))
			return (ft_splitfree(normalized, (size_t)y), NULL);
		y++;
	}
	return (normalized);
}
