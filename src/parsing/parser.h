/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:21:33 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/12 08:56:00 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdint.h>

# include "cub3d.h"
# include "cubmap.h"

bool	is_dot_cub(const char *path);
int16_t	parse_cub(const char *map_path, t_map *out);

int16_t	parse_identifiers(int fd, t_map *m, char **first_line_of_map);
int16_t	parse_grid(int fd, t_map *m, char **first_line_of_map);
int16_t	validate_map_closed(const t_map *m);

#endif
