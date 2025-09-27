/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmath_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:07:26 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/27 12:55:23 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMATH_UTILS_H
# define FTMATH_UTILS_H

# include <stdint.h>
# include <math.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

void	ftm_swap(int32_t *a, int32_t *b);
double	ftm_clamp(double val, double min, double max);
/* Conversions */
double	ftm_rad_to_deg(double angle);
double	ftm_deg_to_rad(double angle);
int32_t	get_y_pos(int32_t map_height, double dev_y);

// *Comp
int32_t	ftm_min(int32_t a, int32_t b);
int32_t	ftm_min3(int32_t a, int32_t b, int32_t c);
int32_t	ftm_max(int32_t a, int32_t b);
int32_t	ftm_max3(int32_t a, int32_t b, int32_t c);

#endif
