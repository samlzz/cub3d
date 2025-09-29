/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_asset.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:05:09 by eazard            #+#    #+#             */
/*   Updated: 2025/09/29 11:00:58 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATED_ASSET_H
# define ANIMATED_ASSET_H


/*mewtwo*/
# define MEWTWO_PATH_00 "./assets/mewtwo/mewtwo000.xpm"
# define MEWTWO_PATH_01 "./assets/mewtwo/mewtwo001.xpm"
# define MEWTWO_PATH_02 "./assets/mewtwo/mewtwo002.xpm"
# define MEWTWO_PATH_03 "./assets/mewtwo/mewtwo003.xpm"
# define MEWTWO_PATH_04 "./assets/mewtwo/mewtwo004.xpm"
# define MEWTWO_PATH_05 "./assets/mewtwo/mewtwo005.xpm"
# define MEWTWO_PATH_06 "./assets/mewtwo/mewtwo006.xpm"
# define MEWTWO_X 36.5
# define MEWTWO_Y 11.5
# define MEWTWO_SPRITE_NB	7

# define ASSET_PATH_SIZE 64

# define SPRITE_NB 1

typedef	struct s_sprite	t_sprite;

struct	s_sprite
{
	double	x;
	double	y;
	t_img	*imgs;
	int32_t	img_nb;
};

#endif