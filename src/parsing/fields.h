/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:26:58 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/29 09:11:46 by sliziard         ###   ########.fr       */
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
	FI__COUNT
};

enum e_field_kind
{
	FK_TEXTURE,
	FK_COLOR
};

typedef enum e_field_id		t_field_id;
typedef enum e_field_kind	t_field_kind;

typedef t_parse_err (*t_value_parser)(const char *value_str, void *dst, struct s_diag *d);
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
	t_value_parser	parser;
	void			*dst;
};

void	fields_init(t_map *map, t_field specs[FI__COUNT]);

t_field_id	fields_check_required(t_field specs[FI__COUNT], bool seen[FI__COUNT]);

t_field_meta	fields_get_metadata(t_field_id id);
void			*fields_get_dst(t_map *m, t_field_id id);
t_value_parser	fields_get_parser(t_field_kind type);

t_field_id		fields_get_by_key(const char *key, size_t len, const t_field *specs);

#endif
