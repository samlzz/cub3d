/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:29:49 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/16 16:10:52 by sliziard         ###   ########.fr       */
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
#include "parsing/parser.h"
#include "str_lst.h"

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

static inline int16_t	_fill_grid(t_grid *g, t_strlst *rows)
{
	int32_t	i;

	i = 0;
	g->dim.x = INT_MIN;
	while (i < g->dim.y && rows)
	{
		g->grid[i++] = rows->str;
		if (rows->str)
		{
			if (!ft_isln_valid(rows->str))
				return (2);
			if (rows->len > g->dim.x)
				g->dim.x = rows->len;
			rows->str = NULL;
		}
		rows = rows->next;
	}
	return (0);
}

int16_t	parse_grid(int fd, t_grid *out)
{
	t_strlst	*head;
	int16_t		code;

	code = 0;
	head = _retrieve_nested_lines(fd, &out->dim.y);
	if (!head)
		return (1 + (out->dim.y == -2));
	out->grid = ft_calloc(out->dim.y + 1, sizeof (char *));
	if (!out->grid)
		return (strlst_clear(head), 1);
	code = _fill_grid(out, head);
	strlst_clear(head);
	if (!code)
		code = validate_map_closed(out);
	return (code);
}

void	free_grid(t_grid *g)
{
	if (!g)
		return ;
	if (g->grid)
		ft_splitfree(g->grid, g->dim.y);
}
