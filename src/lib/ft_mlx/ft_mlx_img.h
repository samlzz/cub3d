/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_img.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:41:20 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 13:45:32 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_IMG_H
# define FT_MLX_IMG_H

# include <stdint.h>

# include "color.h"
# include "vec/vec.h"

typedef struct s_img		t_img;

struct s_img
{
	void	*image_ptr;
	char	*data_addr;
	int32_t	bpp;
	int32_t	endian;
	int32_t	line_len;
	t_vec2i	dim;
};

void		ft_mlx_img_put_px(t_img *img, t_vec2i pos, uint32_t color);
uint32_t	ft_mlx_img_get_px(const t_img *img, t_vec2i pos);

void		ft_mlx_img_put_span(t_img *img, t_vec2iv2 xline, t_color color);
void		ft_mlx_img_put_sphere(t_img *img, t_vec2i pos, int32_t diameter,
			t_color color);

void		ft_mlx_img_put_rect(t_img *img, int32_t thick, t_color color);
void		ft_mlx_img_put_square(t_img *img, t_vec2i start,
			const t_vec2i end, const t_color filled);

int32_t		ft_mlx_img_put_line(t_img *img, t_vec2i start, t_vec2i end,
			t_color color);

void		ft_mlx_img_put_triangle(t_img *img, t_vec2iv3 triangle, t_color color);

#endif
