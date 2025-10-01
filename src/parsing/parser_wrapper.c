/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 00:10:29 by sliziard          #+#    #+#             */
/*   Updated: 2025/10/01 10:23:40 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "ft_gnl.h"
#include "color.h"
#include "str_lst.h"
#include "parse_utils.h"
#include "fields.h"
#include "parsing/parse_err.h"
#include "parsing/parser.h"

t_parse_err	parse_texture_wrap(const char *after_id,
				void *tex_path, struct s_diag *d)
{
	char		*tmp;
	const char	*end;
	size_t		len;

	after_id = ft_skip_sp(after_id);
	len = 0;
	while (after_id[len] && !ft_isspace(after_id[len]))
		len++;
	end = ft_skip_sp(after_id + len);
	if (*end)
	{
		d->what = ft_strdup("trailing content after texture path");
		if (!d->what)
			return (perror("cub3d: parse_texture"), PE_INTERNAL);
		return (PE_U_MALFORMED);
	}
	tmp = ft_substr(after_id, 0, len);
	if (!tmp)
		return (perror("cub3d: parse_texture"), PE_INTERNAL);
	*(char **)tex_path = tmp;
	return (PE_OK);
}

t_parse_err	parse_color_wrap(const char *after_id,
				void *color, struct s_diag *d)
{
	int16_t	code;

	code = parse_rgb_line(after_id, (t_color *)color);
	if (code == 0)
		return (PE_OK);
	if (code == 1)
		d->what = ft_strdup("unexpected separator between digits");
	else if (code == 2)
		d->what = ft_strdup("RGB component out of range (0..255)");
	else if (code == 3)
		d->what = ft_strdup("trailing content after color");
	if (!d->what)
		return (perror("cub3d: parse_color"), PE_INTERNAL);
	if (code == 3)
		return (PE_U_TRAILING_CONTENT);
	return (PE_U_MALFORMED);
}

/* Retrieve files content in a nested list
	Increment size but not initialize it, it's caller responsability
	If an empty line occurs in the middle of the file content:
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

t_parse_err	parse_rest_wrap(int fd, char *first_ln, t_parser *p)
{
	t_parse_err	code;
	t_strlst	*head;
	int32_t		size;

	size = 0;
	head = _retrieve_map_lines(fd, first_ln, &size);
	if (!head && size == -1)
		return (PE_INTERNAL);
	else if (!head)
	{
		p->diag.file_line += size;
		p->diag.what = ft_strdup("empty line in map content");
		return (!p->diag.what * PE_INTERNAL + !!p->diag.what * PE_U_MALFORMED);
	}
	code = parse_map(head, size, &p->out->g, &p->diag);
	strlst_clear(head);
	return (code);
}
