/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:13:59 by eazard            #+#    #+#             */
/*   Updated: 2025/09/18 17:36:19 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx_img.h"
#include "render.h"
#include "vec/vec.h"

/*
 ? & mask (8355711) => 01111111011111110111111101111111
*/
void	dda_algorithm(t_data *data, t_dda_data *dda)
{
	init_dda(data, dda);
	dda_loop(data, dda);
	deduce_wall_orientation(dda);
	deduce_perp_wall_dist(data, dda);
	deduce_wall_band_size(data, dda);
	deduce_wall_x(data, dda);
	deduce_texture_related_data(data, dda);
	draw_bend_with_textue(data, dda);
	// data->camera.zbuf = dda->perp_wall_dist;
}
