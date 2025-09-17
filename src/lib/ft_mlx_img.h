/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_img.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:24:12 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/17 16:59:42 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_IMG_H
# define FT_MLX_IMG_H

# include <stdint.h>

# include "color.h"
# include "vec/vec.h"

typedef struct s_img	t_img;

void	ft_mlx_img_put_px(t_img *img, t_vec2i pos, uint32_t color);
void	ft_mlx_img_fill(t_img *img, t_vec2i start, const t_vec2i end, const t_color filled);

#endif
