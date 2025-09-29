/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_assets_in_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:54:08 by eazard            #+#    #+#             */
/*   Updated: 2025/09/29 11:28:25 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animated_asset.h"
#include "cubmap.h"
#include "data/data.h"

t_sprite	build_a_sprite(double x, double y, t_img *imgs, int32_t img_nb)
{
	t_sprite	s;

	s.x = x;
	s.y = y;
	s.imgs = imgs;
	s.img_nb = img_nb;
	return (s);
}

void	build_all_sprites(t_sprite sprites[SPRITE_NB], t_assets *assets)
{
		sprites[0] = build_a_sprite(MEWTWO_X, MEWTWO_Y, assets->mewtwo_imgs,
				MEWTWO_SPRITE_NB);
}