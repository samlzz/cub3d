/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:02:44 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/05 10:20:19 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

#include "cubmap.h"

void	free_map(t_map *m)
{
	t_directions	d;
	int32_t			i;

	free(m->ceil_colr);
	free(m->floor_colr);
	d = 0;
	while (d < DIR_MAX)
		free(m->tex_paths[d++]);
	i = 0;
	while (i < m->dimensions.y)
		free(m->grid[i++]);
	free(m->grid);
}
