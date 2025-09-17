/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:46:26 by eazard            #+#    #+#             */
/*   Updated: 2025/09/17 19:59:50 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

// ?Ceiling
# define SKY_BLUE     0x87CEEB
# define LIGHT_GRAY   0xD3D3D3
# define BEIGE        0xF5F5DC

// ?Ground
# define DARK_GRAY    0x2F4F4F
# define BROWN        0x8B4513
# define SAND         0xC2B280

// ?Walls
# define RED          0xFF0000
# define GREEN        0x00FF00
# define BLUE         0x0000FF
# define YELLOW       0xFFFF00
# define PURPLE       0x800080
# define CYAN         0x00FFFF
# define ORANGE       0xFFA500
# define WHITE        0xFFFFFF
# define BLACK        0x000000

# if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

struct s_color
{
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;
	uint8_t	a;
};
# else

struct s_color
{
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
};
# endif

typedef union u_color	t_color;

union u_color
{
	struct s_color	code;
	uint32_t		value;
};

// *Parsing

int16_t	parse_rgb_triplet(const char *s, const char **end, t_color **out);
int16_t	parse_rgb_line(const char *s, t_color **out);

#endif
