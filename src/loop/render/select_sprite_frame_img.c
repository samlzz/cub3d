/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_sprite_frame_img.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:09:20 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 18:00:11 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef CUB3D_BONUS

# include "render.h"

static int	get_frame_index(t_data *data, int number_of_frame)
{
	return ((int)(data->camera.current_frame_time) % number_of_frame);
}

void	select_sprite_frame_img(t_data *data,
			t_sprite_rendering_data *sprite_data, t_sprite *sprite)
{
	sprite_data->frame_index = 0;
	sprite_data->frame_asset_img
		= sprite->frames[get_frame_index(data, sprite->count)];
}

#endif
