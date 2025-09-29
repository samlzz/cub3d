/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:50:00 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/29 09:11:28 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

#include "libft.h"
#include "fields.h"
#include "cubmap.h"
#include "parser.h"

t_field_meta	fields_get_metadata(t_field_id id)
{
	static const t_field_meta	_fields_meta[FI__COUNT] = {
	{ "NO",   FK_TEXTURE, true,  "North texture (XPM file)." },
	{ "SO",   FK_TEXTURE, true,  "South texture (XPM file)." },
	{ "WE",   FK_TEXTURE, true,  "West texture (XPM file)." },
	{ "EA",   FK_TEXTURE, true,  "East texture (XPM file)." },
	{ "DOOR", FK_TEXTURE, false, "Door texture (optional)." },
	{ "F",    FK_COLOR,   true,  "Floor color: R,G,B (0..255)." },
	{ "C",    FK_COLOR,   true,  "Ceiling color: R,G,B (0..255)." }
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
	if (id == FI_DOOR)
		return (void *)&m->textures[TEX_DOOR].path;
	if (id == FI_FLOOR)
		return (void *)&m->floor_colr;
	if (id == FI_CEIL)
		return (void *)&m->ceil_colr;
	return (NULL);
}

t_value_parser	fields_get_parser(t_field_kind type)
{
	if (type == FK_COLOR)
		return (&parse_color_wrap);
	if (type == FK_TEXTURE)
		return (&parse_texture_wrap);
	return (NULL);
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
