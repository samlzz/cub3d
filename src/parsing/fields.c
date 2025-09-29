/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:50:00 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/29 12:50:36 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>

#include "libft.h"
#include "fields.h"
#include "cubmap.h"
#include "parser.h"

t_field_meta	fields_get_metadata(t_field_id id)
{
	static const t_field_meta	_fields_meta[FI__COUNT] = {
	{ "NO", FK_TEXTURE, true, "North texture (XPM file)." },
	{ "SO", FK_TEXTURE, true, "South texture (XPM file)." },
	{ "WE", FK_TEXTURE, true, "West texture (XPM file)." },
	{ "EA", FK_TEXTURE, true, "East texture (XPM file)." },
	{ "F", FK_COLOR, true, "Floor color: R,G,B (0..255)." },
	{ "C", FK_COLOR, true, "Ceiling color: R,G,B (0..255)." },
	{ "MAP", FK_REST, true, "Grid content until EOF."},
	};
	return (_fields_meta[id]);
}

void	*fields_get_dst(t_map *m, t_field_id id)
{
	if (id == FI_NO)
		return (void *)&m->textures[TEX_N].path;
	if (id == FI_SO)
		return (void *)&m->textures[TEX_S].path;
	if (id == FI_WE)
		return (void *)&m->textures[TEX_W].path;
	if (id == FI_EA)
		return (void *)&m->textures[TEX_E].path;
	if (id == FI_FLOOR)
		return (void *)&m->floor_colr;
	if (id == FI_CEIL)
		return (void *)&m->ceil_colr;
	return (NULL);
}

t_parse_fn	fields_get_parser(t_field_kind type)
{
	t_parse_fn	fn;

	ft_bzero(&fn, sizeof (t_parse_fn));
	if (type == FK_COLOR)
		fn.head = &parse_color_wrap;
	else if (type == FK_TEXTURE)
		fn.head = &parse_texture_wrap;
	else if (type == FK_REST)
		fn.rest = &parse_rest_wrap;
	return (fn);
}

void	fields_init(t_map *map, t_field *specs, t_field_id end)
{
	t_field_id	i;
	t_field		*curr;

	i = 0;
	while (i < end)
	{
		curr = specs + i;
		curr->id = i;
		curr->metadata = fields_get_metadata(i);
		curr->dst = fields_get_dst(map, i);
		curr->parser = fields_get_parser(curr->metadata.kind);
		i++;
	}
}

t_field_id	fields_get_by_key(const char *key, size_t len, const t_field *specs)
{
	t_field_id	i;

	i = 0;
	while (i < FI__COUNT)
	{
		if (!ft_strncmp(specs[i].metadata.key, key, len)
			&& !specs[i].metadata.key[len])
			return (i);
		i++;
	}
	return (-1);
}
