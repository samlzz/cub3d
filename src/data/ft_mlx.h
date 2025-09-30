/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 08:49:57 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 08:52:28 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_H
# define FT_MLX_H

# include <stdint.h>

typedef struct s_img	t_img;
typedef struct s_mlx	t_mlx;

struct s_img
{
	void	*image_ptr;
	char	*data_addr;
	int32_t	bpp;
	int32_t	endian;
	int32_t	line_len;
	int32_t	width;
	int32_t	height;
};

struct s_mlx
{
	void	*window;
	void	*display;
	t_img	img;
};

#endif