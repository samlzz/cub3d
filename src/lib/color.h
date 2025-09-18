/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:46:26 by eazard            #+#    #+#             */
/*   Updated: 2025/09/18 15:58:35 by eazard           ###   ########.fr       */
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

# define SOUTH_COLOR	ORANGE
# define NORTH_COLOR	BLUE
# define EST_COLOR		GREEN
# define WEST_COLOR		PURPLE
# define CEILING_COLOR	BLACK
# define FLOOR_COLOR	WHITE

/* --- Compat endianness (Linux/macOS) --- */
# if !defined(__BYTE_ORDER__)
#  if defined(__APPLE__)
#   include <machine/endian.h>
#   define __BYTE_ORDER__ BYTE_ORDER
#   define __ORDER_LITTLE_ENDIAN__ LITTLE_ENDIAN
#   define __ORDER_BIG_ENDIAN__    BIG_ENDIAN
#  else
#   include <endian.h>
#  endif
# endif

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

enum	e_compil_time_check
{
	s_color_must_be_4_bytes = 1 / (int)(sizeof (struct s_color) == 4)
};

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

