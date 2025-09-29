/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 22:36:01 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/29 09:24:07 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "ft_gnl.h"
#include "libft.h"
#include "parser.h"
#include "parse_utils.h"
#include "parsing/fields.h"
#include "parsing/parse_err.h"

static t_parse_err	_parse_header_line(const char *line, t_parser *p)
{
	const char	*s;
	size_t		key_len;
	t_field_id	id;

	s = ft_skip_sp(line);
	key_len = 0;
	while (s[key_len] && !ft_isspace(s[key_len]))
		key_len++;
	id = fields_get_by_key(s, key_len, p->specs);
	if (id < 0)
	{
		p->phase = PPH_MAP;
		return (PE_OK);
	}
	p->seen[id] = true;
	p->diag.owner = id;
	return (p->specs[id].parser(s + key_len, p->specs[id].dst, &p->diag));
}

static inline t_parse_err	_handle_eof_err(t_parser *p)
{
	p->diag.what = ft_strdup("unexpected end of file");
	if (!p->diag.what)
		return (perror("cub3d: parse_cub: ft_strdup"), PE_INTERNAL);
	return (PE_U_MALFORMED);
}

static t_parse_err	_parse_flow(int fd, t_parser *p)
{
	char		*line;
	ssize_t		gnl_ret;
	t_parse_err	code;

	while (p->phase == PPH_HEADER)
	{
		gnl_ret = ft_getline(&line, fd);
		if (gnl_ret < 0)
			return (ft_putendl_fd("cub3d: ft_getline: internal err", 2), 1);
		if (!line)
			return (_handle_eof_err(p));
		if (*line != '\n')
		{
			code = _parse_header_line(line, p);
			if (code)
				return (free(line), code);
			if (p->phase == PPH_MAP)
				return (parse_map_flow(fd, line, p));
		}
		free(line);
		p->diag.file_line++;
	}
	return (PE_U_MAP_MISSING);
}

/* Return 1 in case of internal error 
			2 in case of user error
	In every case, error should be already printed */
int16_t	parse_cub(const char *map_path, t_map *out)
{
	t_parser		p;
	int				fd;
	int16_t			code;

	ft_bzero(&p, sizeof (t_parser));
	fields_init(out, p.specs);
	p.out = out;
	p.diag.owner = FI_INVALID;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (open_err(map_path), 1);
	p.diag.filename = map_path;
	code = _parse_flow(fd, &p);
	close(fd);
	if (code)
		return (pe_quit(&p, code), 1 + (code =! 1));
	p.diag.owner = fields_check_required(p.specs, p.seen);
	if (p.diag.owner != -1)
		return (pe_quit(&p, PE_U_MISSING_REQUIRED), 2);
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
