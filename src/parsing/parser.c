/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:39:11 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/12 13:12:56 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "cub3d.h"
#include "cub3d.h"
#include "ft_gnl.h"
#include "libft.h"
#include "str_lst.h"
#include "vec.h"
#include "parser.h"

static t_strlst	*_retrieve_nested_lines(int fd, int32_t	*size,
					char **first_line_of_map)
{
	char		*line;
	t_strlst	*head;
	t_strlst	*new;

	head = NULL;
	line = *first_line_of_map; // on process d'abord
	while (line || ft_getline(&line, fd) > 0)
	{
		if (!line)
			return (strlst_clear(head), NULL);
		if (*line == '\n')
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
		line = NULL;
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

int16_t	parse_grid(int fd, t_map *m, char **first_line_of_map)
{
	t_strlst	*head;

	head = _retrieve_nested_lines(fd, &m->dimensions.y, first_line_of_map);
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
	char	*first_line_of_map;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (1);
	code = parse_identifiers(fd, out, &first_line_of_map);
	if (code)
		return (close(fd), code);
	code = parse_grid(fd, out, &first_line_of_map);
	close(fd);
	code = validate_map_closed(out);
	if (code)
		return (free_map(out), code);
	update_x_dim(out);
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
