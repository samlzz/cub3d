/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:21:33 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/13 17:34:01 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdint.h>

# include "cubmap.h"

// *Parser
bool	is_dot_cub(const char *path);
int16_t	parse_cub(const char *map_path, t_map *out);

// identifiers
int16_t	parse_identifiers(int fd, t_map *m);

// grid
int16_t	parse_grid(int fd, t_map *m);
char	**get_normalized_grid(const t_map *m, t_vec2i *out_dim);

int16_t	validate_map_closed(const t_map *m);

#endif
