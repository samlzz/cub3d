/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:26:58 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 14:53:41 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIELDS_H
# define FIELDS_H

# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>

/* ? forwards declarations */
typedef struct s_map	t_map;
typedef enum e_parse_err	t_parse_err;
struct s_diag;
struct s_parser;

# ifdef CUB3D_BONUS

enum e_field_id
{
	FI_INVALID = -1,
	FI_NO,
	FI_SO,
	FI_EA,
	FI_WE,
	FI_DOOR,
	FI_FLOOR,
	FI_CEIL,
	FI_MAP,
	FI__COUNT
};
# else

enum e_field_id
{
	FI_INVALID = -1,
	FI_NO,
	FI_SO,
	FI_EA,
	FI_WE,
	FI_FLOOR,
	FI_CEIL,
	FI_MAP,
	FI__COUNT
};
# endif

enum e_field_kind
{
	FK_TEXTURE,
	FK_COLOR,
	FK_REST
};

typedef enum e_field_id		t_field_id;
typedef enum e_field_kind	t_field_kind;

typedef t_parse_err (*t_value_parser)(const char *value_str, void *dst, struct s_diag *d);
typedef t_parse_err (*t_rest_parser)(int fd, char *first_line, struct s_parser *p);
typedef union u_parse_fn	t_parse_fn;
union u_parse_fn
{
	t_value_parser	head;
	t_rest_parser	rest;
};

typedef struct s_field_meta	t_field_meta;
typedef struct s_field		t_field;

struct s_field_meta
{
	const char		*key;
	t_field_kind	kind;
	bool			required;
	const char		*help;
};
struct s_field
{
	t_field_meta	metadata;
	t_field_id		id;
	t_parse_fn		parser;
	void			*dst;
};

void			fields_init(t_map *map, t_field *specs, t_field_id end);

t_field_id		fields_get_by_key(const char *key, size_t len, const t_field *specs);

#endif
