/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:17:11 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/29 12:39:46 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>

#include "ft_gnl.h"
#include "libft.h"
#include "parser.h"
#include "parse_utils.h"
#include "fields.h"
#include "parse_err.h"

static t_parse_err	_parse_header_line(const char *line, t_parser *p, bool *switch_rest)
{
	const char	*s;
	size_t		key_len;
	t_field_id	id;
	t_parse_err	exit_code;

	s = ft_skip_sp(line);
	key_len = 0;
	while (s[key_len] && !ft_isspace(s[key_len]))
		key_len++;
	id = fields_get_by_key(s, key_len, p->specs);
	if (id < 0 || p->specs[id].metadata.kind == FK_REST)
	{
		*switch_rest = true;
		return (PE_OK);
	}
	p->diag.owner = id;
	if (p->seen[id])
		return (PE_U_DUPLICATE);
	p->seen[id] = true;
	exit_code = p->specs[id].parser.head(s + key_len, p->specs[id].dst, &p->diag);
	if (exit_code == PE_OK)
		p->diag.owner = FI_INVALID;
	return (exit_code);
}

static inline t_parse_err	_handle_eof_err(t_parser *p)
{
	p->diag.what = ft_strdup("unexpected end of file");
	if (!p->diag.what)
		return (perror("cub3d: parse_cub: ft_strdup"), PE_INTERNAL);
	return (PE_U_MALFORMED);
}

static t_parse_err	_parse_header_flow(int fd, t_parser *p, char **trailing_line)
{
	char		*line;
	ssize_t		gnl_ret;
	t_parse_err	code;
	bool		rest;

	rest = false;
	while (!rest)
	{
		gnl_ret = ft_getline(&line, fd);
		if (gnl_ret < 0)
			return (ft_putendl_fd("cub3d: ft_getline: error", 2), PE_INTERNAL);
		if (!line)
			return (_handle_eof_err(p));
		if (*line != '\n')
		{
			code = _parse_header_line(line, p, &rest);
			if (code)
				return (free(line), code);
		}
		if (rest)
			*trailing_line = line;
		else if ((free(line), 1))
			p->diag.file_line++;
	}
	return (PE_OK);
}

/* Call _parse_header_flow then check required fields (except for REST one)

Call the rest parser on the left content of the file

Handle errors 
	(missing a required field, missing rest field, trailing content but no rest field)
*/
t_parse_err	parse_flow(int fd, t_parser *p)
{
	char			*not_consumed_line;
	t_parse_err		code;
	t_field_id		i;
	t_rest_parser	rest_fn;

	not_consumed_line = NULL;
	code = _parse_header_flow(fd, p, &not_consumed_line);
	if (code)
		return (code);
	i = -1;
	rest_fn = NULL;
	while (++i < FI__COUNT)
	{
		if (p->specs[i].metadata.kind == FK_REST)
			rest_fn = p->specs[i].parser.rest;
		else if (p->specs[i].metadata.required && !p->seen[i])
			return (p->diag.owner = i, PE_U_MISSING_REQUIRED);
	}
	if (rest_fn && not_consumed_line)
		return (rest_fn(fd, not_consumed_line, p));
	if (rest_fn)
		return (PE_U_MAP_MISSING);
	if (not_consumed_line)
		return (p->diag.what = not_consumed_line, PE_U_TRAILING_CONTENT);
	return (PE_OK);
}
