/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:21:30 by eazard            #+#    #+#             */
/*   Updated: 2025/09/10 15:10:23 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>
# include "cub3d.h"

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
typedef union u_color	t_color;

t_color	*parse_rgb_triplet(const char *s, const char **end);
t_color	*parse_rgb_line(const char *s);

#endif