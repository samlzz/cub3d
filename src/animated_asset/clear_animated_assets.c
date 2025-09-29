/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_animated_assets.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 09:35:12 by eazard            #+#    #+#             */
/*   Updated: 2025/09/29 09:42:04 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data/data.h"
#include "mlx.h"

static void	fatal_clear_an_asset(t_mlx *mlx, t_img *asset_imgs, size_t img_nb)
{
	size_t	i;

	i = 0;
	while (i < img_nb)
	{
		if (asset_imgs[i].image_ptr)
			mlx_destroy_image(mlx->display, asset_imgs[i].image_ptr);
		else
			return ;
		i++;
	}
}

void	fatal_clear_animated_assets(t_mlx *mlx, t_assets *assets)
{
	fatal_clear_an_asset(mlx, assets->mewtwo_imgs, MEWTWO_SPRITE_NB);
}
