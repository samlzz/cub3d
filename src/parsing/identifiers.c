/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:54:51 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/18 10:13:45 by sliziard         ###   ########.fr       */
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
#include "parse_utils.h"
#include "cubmap.h"

static inline int16_t	_dispatch_textures(char **tex_paths, const char *id, size_t id_len)
{
	t_directions	tex_dir;
	size_t			len;

	if (!ft_strncmp(id, "NO", id_len))
		tex_dir = DIR_N;
	else if (!ft_strncmp(id, "SO", id_len))
		tex_dir = DIR_S;
	else if (!ft_strncmp(id, "WE", id_len))
		tex_dir = DIR_W;
	else if (!ft_strncmp(id, "EA", id_len))
		tex_dir = DIR_E;
	else
		return (2);
	id += id_len;
	id = ft_skip_sp(id);
	len = 0;
	while (id[len] && !ft_isspace(id[len]))
		len++;
	tex_paths[tex_dir] = ft_substr(id, 0, len);
	if (!tex_paths[tex_dir])
		return (perror("cub3d: parse_identifiers: malloc"), 1);
	return (!(*ft_skip_sp(id + len) == '\0'));
}

static int16_t	_fill_identifiers(const char *ln, t_map *m)
{
	size_t	n;
	int16_t	code;
	
	ln = ft_skip_sp(ln);
	n = 0;
	while (ln && !ft_isspace(ln[n]))
		n++;
	if (!n || !ln[n])
		return (2);
	if (*ln == 'F' && n == 1)
		code = parse_rgb_line(ln + 1, &m->floor_colr);
	else if (*ln == 'C' && n == 1)
		code = parse_rgb_line(ln + 1, &m->ceil_colr);
	else
		return (_dispatch_textures(m->tex_paths, ln, n));
	return (code);
}

static inline bool	_identifiers_filled(t_map *m)
{
	return (m->ceil_colr && m->floor_colr 
		&& m->tex_paths[DIR_N] && m->tex_paths[DIR_S]
		&& m->tex_paths[DIR_E] && m->tex_paths[DIR_W]);
}

int16_t	parse_identifiers(int fd, t_map *m)
{
	char	*line;
	int16_t	code;

	line = NULL;
	while (!_identifiers_filled(m) && ft_getline(&line, fd) > 0)
	{
		if (!line)
			return (1);
		if (*line != '\n')
		{
			code = _fill_identifiers(line, m);
			if (code)
				return (free(line), code);
		}
		free(line);
	}
	return (0);
}
