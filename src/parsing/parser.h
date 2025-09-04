/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:21:33 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/04 13:31:40 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdint.h>

# include "cubmap.h"

int16_t	parse_cub(const char *map_path, t_map *out);

int16_t	parse_identifiers(int fd, t_map *m);
int16_t	parse_grid(int fd, t_map *m);
int16_t	validate_map_closed(const t_map *m);
int16_t	normalize_map(t_map *m);

#endif
