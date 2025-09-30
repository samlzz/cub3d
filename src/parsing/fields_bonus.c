/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:50:00 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 15:41:21 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef CUB3D_BONUS

# include <stdbool.h>

# include "fields.h"

t_field_meta	fields_get_metadata(t_field_id id)
{
	static const t_field_meta	_fields_meta[FI__COUNT] = {
	{ "NO", FK_TEXTURE, true, "North texture (XPM file)." },
	{ "SO", FK_TEXTURE, true, "South texture (XPM file)." },
	{ "EA", FK_TEXTURE, true, "East texture (XPM file)." },
	{ "WE", FK_TEXTURE, true, "West texture (XPM file)." },
	{ "D", FK_TEXTURE, true, "Door texture (XPM file)."},
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
	if (id == FI_EA)
		return (void *)&m->textures[TEX_E].path;
	if (id == FI_WE)
		return (void *)&m->textures[TEX_W].path;
	if (id == FI_DOOR)
		return (void *)&m->textures[TEX_DOOR].path;
	if (id == FI_FLOOR)
		return (void *)&m->floor_colr;
	if (id == FI_CEIL)
		return (void *)&m->ceil_colr;
	return (NULL);
}

#endif
