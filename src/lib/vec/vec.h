/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:23:12 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/20 22:02:21 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <stddef.h>
# include <stdint.h>

typedef struct s_vec2i		t_vec2i;
typedef struct s_vec2d		t_vec2d;

struct s_vec2i
{
	int32_t	x;
	int32_t	y;
};

struct s_vec2d
{
	double	x;
	double	y;
};

// *Functions

/* vector of double */
void	vec2d_rotate(t_vec2d *vec, double angle);
t_vec2d	vec2d_sum(t_vec2d vec1, t_vec2d vec2);
t_vec2d	vec2d_scalar_mult(t_vec2d vec, double scalar);
t_vec2i	vec2d_round(t_vec2d vec, bool round_greater);

void	vec2d_print(t_vec2d vec, char *name);

/* vector of integer */
t_vec2i	vec2i_sum(t_vec2i vec1, t_vec2i vec2);
t_vec2i	vec2i_minus(t_vec2i vec1, t_vec2i vec2);
t_vec2i	vec2i_scalar_mult(t_vec2i vec, double scalar);
t_vec2i	vec2i_clamp(t_vec2i vec, t_vec2i min, t_vec2i max);

void	vec2i_print(t_vec2i vec, char *name);

#endif
