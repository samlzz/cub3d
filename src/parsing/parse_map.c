/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:21:24 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/28 18:48:56 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "cubmap.h"
#include "libft.h"
#include "ft_gnl.h"
#include "parsing/parse_err.h"
#include "str_lst.h"
#include "fields.h"
#include "parser.h"
#include "parse_utils.h"

/* Retrieve files content in a nested list
	Increment size but not initialize it, it's caller responsability
	If an empty line occurs in the middle of the map content:
		kepp *size value
	If an internal error occurs:
		set *size to -1
	and return NULL
	*/
static t_strlst	*_retrieve_map_lines(int fd, char *first_ln, int32_t *size)
{
	t_strlst	*head;
	char		*line;
	ssize_t		gnl_ret;
	bool		trailing_blank;

	head = NULL;
	trailing_blank = false;
	line = first_ln;
	while (line)
	{
		if (ft_isln_empty(line))
		{
			trailing_blank = true;
			free(line);
		}
		else if (trailing_blank)
			return (strlst_clear(head), free(line), NULL);
		else if (strlst_add_node(&head, line, size))
			return (strlst_clear(head), free(line), *size = -1, NULL);
		gnl_ret = ft_getline(&line, fd);
		if (gnl_ret < 0)
			return (strlst_clear(head), *size = -1, NULL);
	}
	return (head);
}

static inline t_parse_err	_handle_invalid_map_ln(struct s_diag *d, int32_t i, char c_err)
{
	d->file_line = i;
	d->what = ft_strjoin("invalid character in map content: ", &c_err);
	if (!d->what)
		return (perror("cub3d: parse_grid: malloc"), PE_INTERNAL);
	return (PE_U_MALFORMED);
}

static t_parse_err	_parse_grid(t_strlst *lines, int32_t count, t_grid *grid, struct s_diag *d)
{
	int32_t	i;
	size_t	err_idx;

	grid->dim.y = count;
	grid->grid = ft_calloc(count + 1, sizeof (char *));
	if (!grid)
		return (perror("cub3d: parse_grid: malloc"), PE_INTERNAL);
	grid->dim.x = INT_MIN;
	i = 0;
	while (i < grid->dim.y && lines)
	{
		grid->grid[i] = lines->str;
		if (lines->str)
		{
			if (!ft_isln_valid(lines->str, &err_idx))
				return (_handle_invalid_map_ln(d, i, lines->str[err_idx]));
			if (lines->len > grid->dim.x)
				grid->dim.x = lines->len;
			lines->str = NULL;
		}
		lines = lines->next;
		i++;
	}
	return (PE_OK);
}

t_parse_err	parse_map_flow(int fd, char *first_line, t_parser *p)
{
	t_parse_err	code;
	t_strlst	*head;
	t_grid		*normalized;
	int32_t		lines_count;

	lines_count = 0;
	head = _retrieve_map_lines(fd, first_line, &lines_count);
	if (!head && lines_count == -1)
		return (PE_INTERNAL);
	else if (!head)
	{
		p->diag.file_line = lines_count;
		p->diag.what = ft_strdup("emtpy line in map content");
		return (PE_U_MALFORMED);
	}
	code = _parse_grid(head, lines_count, &p->out->g, &p->diag);
	strlst_clear(head);
	if (code)
		return (code);
	normalized = get_normalized_grid(&p->out->g);
	if (!normalized)
		return (PE_INTERNAL);
	code = validate_map_closed(normalized);
	return (free_grid(normalized), free(normalized), code);
}
