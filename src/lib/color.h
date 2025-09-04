/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:46:26 by eazard            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/09/05 10:58:57 by sliziard         ###   ########.fr       */
=======
/*   Updated: 2025/09/04 16:01:57 by eazard           ###   ########.fr       */
>>>>>>> ca79e70 (feat(camera) add of camera struct and camera rotation)
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

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