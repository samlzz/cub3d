/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:29:49 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/11 14:34:18 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "cubmap.h"
#include "parse_utils.h"
#include "ft_gnl.h"
#include "libft.h"
#include "str_lst.h"

static inline bool	_is_empty_line(const char *ln)
{
	size_t	i;
	size_t	len;
	
	len = ft_strlen(ln);
	i = 0;
	while (ft_isspace(ln[i]))
		i++;
	return (i == len);
}

static t_strlst	*_retrieve_nested_lines(int fd, int32_t	*size)
{
	char		*line;
	t_strlst	*head;
	t_strlst	*new;
	bool		empty_ln;

	head = NULL;
	while (ft_getline(&line, fd) > 0)
	{
		if (!line)
			return (strlst_clear(head), NULL);
		if (_is_empty_line(line))
		{
			empty_ln = true;
			free(line);
			continue ;
		}
		if (empty_ln)
			return (strlst_clear(head), free(line), *size = -2, NULL);
		new = strlst_new(line);
		if (!new)
			return (strlst_clear(head), free(line), NULL);
		strlst_addback(&head, new);
		(*size)++;
	}
	return (head);
}

static inline void	_fill_grid(t_map *m, t_strlst *rows)
{
	int32_t	i;
	char	*ln;

	i = 0;
	while (i < m->dimensions.y && rows)
	{
		m->grid[i++] = rows->str;
		if (rows->str)
		{
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
