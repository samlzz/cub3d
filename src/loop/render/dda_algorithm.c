/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:13:59 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 17:39:48 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	dda_algorithm(t_data *data, t_dda_data *dda)
{
	init_dda(data, dda);
	dda_loop(data, dda);
	deduce_wall_orientation(dda);
	deduce_perp_wall_dist(data, dda);
	deduce_wall_band_size(dda);
	deduce_wall_x(data, dda);
	deduce_texture_related_data(data, dda);
	draw_bend_with_textue(data, dda);
}
