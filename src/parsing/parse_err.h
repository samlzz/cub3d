/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_err.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 23:12:46 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/29 11:21:14 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_ERR_H
# define PARSE_ERR_H

# include "parsing/fields.h"
# include <stdint.h>

typedef struct s_parser 	t_parser;
typedef enum e_parse_err	t_parse_err;

enum e_parse_err
{
	PE_OK = 0,
	PE_INTERNAL,
	PE_U_DUPLICATE,
	PE_U_MALFORMED,
	PE_U_UNKNOW_KEY,
	PE_U_MISSING_REQUIRED,
	PE_U_MAP_MISSING,
	PE_U_MAP_PLAYER_MISSING,
	PE_U_MAP_PLAYER_MANY,
	PE_U_MAP_OPEN,
	PE_U_MAP_NO_WALKABLE,
	PE_U_TRAILING_CONTENT,
	PE__COUNT
};

struct s_diag
{
	const char	*filename;
	int32_t		file_line;
	t_field_id	owner;
	char		*what;
};

void	open_err(const char *filename);

void	pe_quit(t_parser *p, t_parse_err code);
void	pe_diag_reset(struct s_diag *d);
void	pe_print_err(const struct s_diag *d,
			const t_field *specs, t_parse_err code);

#endif
