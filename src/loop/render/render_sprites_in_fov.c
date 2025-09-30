/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites_in_fov.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:49:28 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 17:34:04 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef CUB3D_BONUS

# include <stddef.h>

# include "render.h"
# include "vec/vec.h"

static void	get_camera_space_coordinate(t_camera *cam, t_sprite *sprite,
					t_vec2d *out)
{
	double	determinent_inverse;
	t_vec2d	distance_to_camera;

	distance_to_camera.x = sprite->pos.x - cam->pos.x;
	distance_to_camera.y = sprite->pos.y - cam->pos.y;
	determinent_inverse = 1.0 / (cam->plane.x * FOV_FACTOR * cam->dir.y
			- cam->dir.x * cam->plane.y * FOV_FACTOR);
	out->x = determinent_inverse * (cam->dir.y * distance_to_camera.x
			- cam->dir.x * distance_to_camera.y);
	out->y = determinent_inverse * (-cam->plane.y \
				* distance_to_camera.x * FOV_FACTOR \
			+ cam->plane.x * distance_to_camera.y * FOV_FACTOR);
}

static inline bool	sprint_isnt_behind_player(
						t_sprite_rendering_data sprite_data)
{
	return (sprite_data.camera_space_coordinate.y > 0.0001);
}

void	render_sprites_in_fov(t_data *data)
{
	t_sprite_rendering_data	sprite_data;
	t_sprite				*printed_sprite;
	size_t					i;

	i = 0;
	while (i < data->map.bank.count)
	{
		sprite_data.printed_sprit_id = data->map.bank.order[i];
		printed_sprite = &data->map.bank.sprites[sprite_data.printed_sprit_id];
		get_camera_space_coordinate(&data->camera, printed_sprite,
			&sprite_data.camera_space_coordinate);
		if (sprint_isnt_behind_player(sprite_data))
		{
			render_a_sprit(data, &sprite_data, printed_sprite);
		}
		i++;
	}
}

#endif
