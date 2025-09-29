/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_animated_assets.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:11:42 by eazard            #+#    #+#             */
/*   Updated: 2025/09/29 10:01:08 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "animated_asset.h"
#include "data/data.h"
#include "libft.h"

void	install_mewtwo_assets_paths(char (*mewtwo_assets)[ASSET_PATH_SIZE])
{
	ft_strlcpy(mewtwo_assets[0], MEWTWO_PATH_00, ASSET_PATH_SIZE);
	ft_strlcpy(mewtwo_assets[1], MEWTWO_PATH_01, ASSET_PATH_SIZE);
	ft_strlcpy(mewtwo_assets[2], MEWTWO_PATH_02, ASSET_PATH_SIZE);
	ft_strlcpy(mewtwo_assets[3], MEWTWO_PATH_03, ASSET_PATH_SIZE);
	ft_strlcpy(mewtwo_assets[4], MEWTWO_PATH_04, ASSET_PATH_SIZE);
	ft_strlcpy(mewtwo_assets[5], MEWTWO_PATH_05, ASSET_PATH_SIZE);
	ft_strlcpy(mewtwo_assets[6], MEWTWO_PATH_06, ASSET_PATH_SIZE);
}

static int16_t	load_an_asset(t_img *asset_imgs, t_mlx *mlx,
			char (*asset_paths)[ASSET_PATH_SIZE], size_t asset_number)
{
	size_t	i;

	i = 0;
	while (i < asset_number)
	{
		if (file_found_and_readable(asset_paths[i]))
		{
			asset_imgs[i] = open_xpm_and_get_its_data(asset_paths[i], mlx);
			if (asset_imgs[i].image_ptr == NULL)
				return (1);
		}
		else
			return (1);
		i++;
	}
	return (0);
}

void	install_animeted_assets_paths(t_assets *assets)
{
	install_mewtwo_assets_paths(assets->mewtwo_paths);
}

int16_t	load_animated_assets(t_assets *assets, t_mlx *mlx)
{
	install_animeted_assets_paths(assets);
	if (load_an_asset(assets->mewtwo_imgs, mlx,
			assets->mewtwo_paths, MEWTWO_SPRITE_NB))
		return (1);
	return (0);
}
