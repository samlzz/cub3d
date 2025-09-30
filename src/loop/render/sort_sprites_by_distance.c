/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites_by_distance.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:49:46 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 09:09:37 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	_ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_sprite(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < SPRITE_NB - 1)
	{
		j = 0;
		while (j < SPRITE_NB - 1 - i)
		{
			if (data->map.sprite_distance_square[data->map.sprite_order[j]]
				< data->map.sprite_distance_square
				[data->map.sprite_order[j + 1]])
				_ft_swap(&data->map.sprite_order[j],
					&data->map.sprite_order[j + 1]);
			j++;
		}
		i++;
	}
}
