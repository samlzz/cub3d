/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_texture.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:12:45 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/27 21:16:32 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_TEXTURE_H
# define FT_MLX_TEXTURE_H

#include <stdint.h>

#include "ft_mlx_img.h"

typedef struct s_texture	t_texture;

struct s_texture
{
	char		*path;
	t_img		*img;
};

int16_t	ft_mlx_texture_load(t_texture *tex);
void	ft_mlx_texture_destroy(t_texture *tex);

#endif
