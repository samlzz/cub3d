/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:31:34 by eazard            #+#    #+#             */
/*   Updated: 2025/09/12 15:40:55 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"

/* colors.h */
#ifndef COLORS_H
# define COLORS_H

// Plafond
# define SKY_BLUE     0x87CEEB
# define LIGHT_GRAY   0xD3D3D3
# define BEIGE        0xF5F5DC

// Sol
# define DARK_GRAY    0x2F4F4F
# define BROWN        0x8B4513
# define SAND         0xC2B280

// Murs
# define RED          0xFF0000
# define GREEN        0x00FF00
# define BLUE         0x0000FF
# define YELLOW       0xFFFF00
# define PURPLE       0x800080
# define CYAN         0x00FFFF
# define ORANGE       0xFFA500
# define WHITE        0xFFFFFF
# define BLACK        0x000000

#endif


typedef struct s_img	t_img;
typedef struct s_line	t_line;

struct s_line
{
	int	column;
	int	y0;
	int	y1;
};



void	put_pixel_in_buffer(t_img *img, int x, int y, int color);
void	draw_clear(t_data *data, uint32_t ceil_color, uint32_t floor_color);
void	draw_vline(t_data *data, t_line line, uint32_t color);
void	render_frame(t_data *data);
#endif