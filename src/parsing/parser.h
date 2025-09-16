/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:21:33 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/16 16:06:56 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdint.h>

# include "cubmap.h"

// *External

bool	is_dot_cub(const char *path);
int16_t	parse_cub(const char *map_path, t_map *out);


// *Internal

// identifiers
int16_t	parse_identifiers(int fd, t_map *m);

// grid
int16_t	parse_grid(int fd, t_grid *out);
void	free_grid(t_grid *g);

int16_t	validate_map_closed(const t_grid *usr_map);

#endif
