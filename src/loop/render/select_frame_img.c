/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_frame_img.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:09:20 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 09:18:15 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int	get_frame_index(t_data *data, int number_of_frame)
{
	return ((int)(data->camera.current_frame_time) % number_of_frame);
}

void	select_frame_img(t_data *data,
			t_asset_data *sprite_data, t_sprite *sprite)
{
	sprite_data->frame_index = 0;
	sprite_data->frame_asset_img
		= sprite->imgs[get_frame_index(data, sprite->img_nb)];
}
