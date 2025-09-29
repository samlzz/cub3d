/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_sprite_number.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:25:54 by eazard            #+#    #+#             */
/*   Updated: 2025/09/29 10:34:15 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animated_asset.h"
#include <stdint.h>
#include "vec/vec.h"
#include "cubmap.h"

static bool	is_a_sprit_char(char c)
{
	return (!(c == 'D' || c == '1' || c == '0' || c == ' ' || c = 'E'
			|| c = 'W' || c == 'N' || c == 'S'));
}

int32_t	count_sprite_number(t_map *map)
{
	int32_t	sprite_nb;
	t_vec2i	index;

	index.y = 0;
	sprite_nb = 0;
	while (index.y < map->g.dim.y)
	{
		while (map->g.grid[index.y][index.x])
		{
			if (is_a_sprit_char(map->g.grid[index.y][index.z]))
				sprite_nb++;
			index.x++;
		}
		index.y++;
	}
	return (sprite_nb);
}
