/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:23:12 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 14:20:04 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>

typedef struct s_vec2i		t_vec2i;
typedef struct s_vec2d		t_vec2d;

typedef struct s_vec2iv2		t_vec2iv2;
typedef struct s_vec2iv3		t_vec2iv3;

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

struct s_vec2iv2
{
	t_vec2i	a;
	t_vec2i	b;
};

struct s_vec2iv3
{
	t_vec2i	a;
	t_vec2i	b;
	t_vec2i	c;
};

// *Functions

/* vector of double */
void	vec2d_rotate(t_vec2d *vec, double angle);
t_vec2i	vec2d_round(t_vec2d vec, bool round_greater);
double	vec2d_get_norm(t_vec2d vec);

/* base operations*/
t_vec2d	vec2d_sum(t_vec2d vec1, t_vec2d vec2);
t_vec2d	vec2d_minus(t_vec2d vec1, t_vec2d vec2);
t_vec2d	vec2d_scalar_mult(t_vec2d vec, double scalar);

void	vec2d_print(t_vec2d vec, char *name);

/* vector of integer */
t_vec2i	vec2i_sum(t_vec2i vec1, t_vec2i vec2);
t_vec2i	vec2i_minus(t_vec2i vec1, t_vec2i vec2);
t_vec2i	vec2i_scalar_mult(t_vec2i vec, double scalar);
t_vec2i	vec2i_clamp(t_vec2i vec, t_vec2i min, t_vec2i max);
void	vec2i_swap(t_vec2i *v1, t_vec2i *v2);

void	vec2i_print(t_vec2i vec, char *name);

#endif
