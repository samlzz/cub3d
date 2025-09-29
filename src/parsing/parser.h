/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 22:10:36 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/28 18:48:48 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

# include "cubmap.h"
# include "fields.h"
# include "parse_err.h"

typedef enum e_parse_phase	t_parse_phase;
typedef struct s_parser		t_parser;

enum	e_parse_phase
{
	PPH_HEADER = 0,
	PPH_MAP
};

struct s_parser
{
	t_map			*out;
	t_field			specs[FI__COUNT];
	bool			seen[FI__COUNT];
	t_parse_phase	phase;
	struct s_diag	diag;
};

int16_t		parse_cub(const char *map_path, t_map *out);
bool		is_dot_cub(const char *path);

t_parse_err	parse_map_flow(int fd, char *first_line, t_parser *p);
t_parse_err	validate_map_closed(const t_grid *normalized);
t_grid		*get_normalized_grid(const t_grid *usr_map);

t_parse_err	parse_color_wrap(const char *after_id, void *color, struct s_diag *d);
t_parse_err	parse_texture_wrap(const char *after_id, void *tex_path, struct s_diag *d);

#endif
