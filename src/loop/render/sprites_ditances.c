/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_ditances.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:56:24 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 14:04:29 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "data/camera.h"
#include "data/sprite.h"
#include "vec/ftmath_utils.h"
#include "vec/vec.h"

void	set_up_sprites_for_sort(t_sprites_data *bank, t_camera *cam)
{
	size_t	i;
	t_vec2d	dist;

	i = 0;
	while (i < bank->count)
	{
		bank->order[i] = i;
		dist = vec2d_minus(cam->pos, bank->sprites[i].pos);
		bank->square_distances[i] = dist.x * dist.x + dist.y * dist.y;
		i++;
	}
}

void	sort_sprite(t_sprites_data *bank)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < bank->count - 1)
	{
		j = 0;
		while (j < bank->count - 1 - i)
		{
			if (bank->square_distances[bank->order[j]]
				< bank->square_distances[bank->order[j + 1]])
				ftm_swap(&bank->order[j], &bank->order[j + 1]);
			j++;
		}
		i++;
	}
}
