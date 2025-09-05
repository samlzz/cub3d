/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:39:11 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/05 12:06:55 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "cubmap.h"
#include "ft_gnl.h"
#include "libft.h"
#include "str_lst.h"
#include "vec.h"
#include "parser.h"

static t_strlst	*_retrieve_nested_lines(int fd, int32_t	*size)
{
	char		*line;
	t_strlst	*head;
	t_strlst	*new;

	head = NULL;
	while (ft_getline(&line, fd))
	{
		if (!line)
			return (strlst_clear(head), NULL);
		if (!*line)
		{
			strlst_clear(head);
			free(line);
			*size = -2;
			return (NULL);
		}
		new = strlst_new(line);
		if (!new)
			return (strlst_clear(head), free(line), NULL);
		strlst_addback(&head, new);
		(*size)++;
		free(line);
	}
	return (head);
}

static inline void	_fill_grid(t_map *m, t_strlst *rows)
{
	int32_t	i;

	i = 0;
	while (i < m->dimensions.y && rows)
	{
		m->grid[i++] = rows->str;
		rows->str = NULL;
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

int16_t	validate_map_closed(const t_map *m)
{
	(void)m;
	return (0);
}

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
	code = validate_map_closed(out);
	if (code)
		return (free_map(out), code);
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