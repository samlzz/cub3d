/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmath_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:07:26 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/17 17:45:07 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMATH_UTILS_H
# define FTMATH_UTILS_H

# include <stdint.h>
# include <math.h>

# include "vec.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

double	vec2d_get_norm(t_vec2d vec);

// *To manipulate angle of t_vec2d:

double	ftm_clamp(double val, double min, double max);
/* Conversions */
double	ftm_rad_to_deg(double angle);
double	ftm_deg_to_rad(double angle);


#endif
