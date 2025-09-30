/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_sprite_dist_and_order.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:52:07 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 08:47:49 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	set_up_sprite_order_and_dist(t_data *data)
{
	int		i;
	double	distance_x;
	double	distance_y;

	i = 0;
	while (i < SPRITE_NB)
	{
		data->map.sprite_order[i] = i;
		distance_x = data->camera.pos.x - data->map.sprites[i].x;
		distance_y = data->camera.pos.y - data->map.sprites[i].y;
		data->map.sprite_distance_square[i]
			= distance_x * distance_x + distance_y * distance_y;
		i++;
	}
}
