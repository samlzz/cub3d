/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:02:44 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/16 15:51:15 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

#include "cubmap.h"
#include "parsing/parser.h"

void	free_map(t_map *m)
{
	t_directions	d;

	free(m->ceil_colr);
	free(m->floor_colr);
	d = 0;
	while (d < DIR_MAX)
		free(m->tex_paths[d++]);
	free_grid(&m->g);
}
