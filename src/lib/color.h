/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:46:26 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 16:12:47 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

typedef union u_color	t_color;

struct s_color
{
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
};

union u_color
{
	struct s_color	code;
	int32_t			value;
};

// *Parsing

int16_t	parse_rgb_triplet(const char *s, const char **end, t_color **out);
int16_t	parse_rgb_line(const char *s, t_color **out);\

#endif