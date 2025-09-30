/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deduce_after_loop_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:09:06 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 17:38:46 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef CUB3D_BONUS

# include "cubmap.h"
# include "render.h"

void	deduce_texture_related_data(t_data *data, t_dda_data *dda)
{
	if (dda->target == 'D')
		dda->tex_img = &data->map.textures[TEX_DOOR].img;
	else
		dda->tex_img = &data->map.textures[dda->wall_orientation].img;
	dda->tex_x = (int)(dda->wall_x * (double)dda->tex_img->dim.x);
	if ((dda->side == 0 && dda->ray_dir.x > 0)
		|| (dda->side == 1 && dda->ray_dir.y < 0))
		dda->tex_x = dda->tex_img->dim.x - dda->tex_x - 1;
	dda->tex_step = (double)dda->tex_img->dim.y
		/ dda->line_height;
	dda->tex_pos = \
		(dda->draw_start - (float)WIN_HEIGHT / 2 + (float)dda->line_height / 2)
		* dda->tex_step;
}

#endif