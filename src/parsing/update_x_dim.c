/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_x_dim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:13:08 by eazard            #+#    #+#             */
/*   Updated: 2025/09/12 13:19:15 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int32_t	get_line_len(char *line)
{
	int32_t	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}



static int32_t	get_x_dim(t_map *map)
{
	int32_t	i;
	int32_t	max;
	int32_t	line_len;

	i = 0;
	max = 0;
	while (i < map->dimensions.y)
	{
		line_len = get_line_len(map->grid[i]);
		if (line_len > max)
			max = line_len;
		i++;
	}
	return (max);
}


void	update_x_dim(t_map *map)
{
	map->dimensions.x = get_x_dim(map);
}
