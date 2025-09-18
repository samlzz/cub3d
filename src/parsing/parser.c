/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:39:11 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/18 10:30:11 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#include "cubmap.h"
#include "error.h"
#include "libft.h"
#include "parser.h"

/**
	Open file at `map_path` and fill `out`

	Return:
		0: exit successfully
		1: internal error (malloc fail, ...)
		2: user error
		3: map open
*/
int16_t	parse_cub(const char *map_path, t_map *out)
{
	int16_t	code;
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (open_err(map_path), 1);
	code = parse_identifiers(fd, out);
	if (code)
		return (close(fd), code);
	code = parse_grid(fd, &out->g);
	close(fd);
	return (code);
}

void	parse_err_print(int16_t code, t_map *to_free)
{
	free_map(to_free);
	if (code == 1)
		return ;
	else if (code == 2)
		return (ft_putendl_fd(ERR_USR_INPUT, 2));
	else if (code == 3)
		return (ft_putendl_fd(ERR_MAP_OPEN, 2));
}

bool	is_dot_cub(const char *path)
{
	char	*dot;

	dot = ft_strrchr(path, '.');
	if (!dot)
		return (false);
	return (!ft_strcmp(dot + 1, "cub"));
}
