/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 22:36:01 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/29 12:46:17 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

#include "libft.h"
#include "parser.h"
#include "parsing/fields.h"
#include "parsing/parse_err.h"

/* Return 1 in case of internal error 
			2 in case of user error
	In every case, error should be already printed */
int16_t	parse_cub(const char *map_path, t_map *out)
{
	t_parser		p;
	int				fd;
	int16_t			code;

	ft_bzero(&p, sizeof (t_parser));
	fields_init(out, p.specs, FI__COUNT);
	p.out = out;
	p.diag.owner = FI_INVALID;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (open_err(map_path), 1);
	p.diag.filename = map_path;
	code = parse_flow(fd, &p);
	close(fd);
	if (code)
		return (pe_quit(&p, code), 1 + (code != 1));
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
