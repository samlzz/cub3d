/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:50:00 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/29 09:15:06 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "fields.h"
#include "cubmap.h"

void	fields_init(t_map *map, t_field specs[FI__COUNT])
{
	t_field_id	i;
	t_field		*curr;

	i = 0;
	while (i < FI__COUNT)
	{
		curr = specs + i;
		curr->id = i;
		curr->metadata = fields_get_metadata(i);
		curr->dst = fields_get_dst(map, i);
		curr->parser = fields_get_parser(curr->metadata.kind);
		i++;
	}
}

t_field_id	fields_check_required(t_field specs[FI__COUNT], bool seen[FI__COUNT])
{
	t_field_id	i;

	i = 0;
	while (i < FI__COUNT)
	{
		if (specs[i].metadata.required && !seen[i])
			return (i);
		i++;
	}
	return (-1);
}
