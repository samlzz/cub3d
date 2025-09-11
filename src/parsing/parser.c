/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:39:11 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/11 14:30:06 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#include "cubmap.h"
#include "libft.h"
#include "parser.h"

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
	if (code)
		return (code);
	code = validate_map_closed(out);
	if (code)
		return (code);
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
