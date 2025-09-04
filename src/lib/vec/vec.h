/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:23:12 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/04 17:29:55 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <stddef.h>
# include <stdint.h>
# include <math.h>
# include <stdio.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

struct s_vec2i
{
	int32_t	x;
	int32_t	y;
};
typedef struct s_vec2i		t_vec2i;

enum e_directions
{
	DIR_N,
	DIR_S,
	DIR_E,
	DIR_W,
	DIR_MAX
};
typedef enum e_directions	t_directions;

struct s_vec2d
{
	double	x;
	double	y;
};
typedef struct s_vec2d		t_vec2d;

/*rotate*/
void	vec_rotate(t_vec2d *vec, double angle);
void	vec_left_rotate(t_vec2d *vec, double angle);
void	vec_right_rotate(t_vec2d *vec, double angle);

/*print*/
void	print_vec2d(t_vec2d vec, char *name);
void	print_vec2i(t_vec2i vec, char *name);

/*convert radian in degree and the oposit*/
double	rad_to_deg(double angle);
double	deg_to_rad(double angle);

#endif
