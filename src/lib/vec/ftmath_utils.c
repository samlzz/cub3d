/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmath_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:08:23 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 15:56:11 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "ftmath_utils.h"

inline double	ftm_clamp(double val, double min, double max)
{
	if (val > max)
		return (max);
	else if (val < min)
		return (min);
	else
		return (val);
}

inline void	ftm_swap(int32_t *a, int32_t *b)
{
	int32_t	tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

inline double	ftm_deg_to_rad(double angle)
{
	return (angle * M_PI / 180);
}

inline double	ftm_rad_to_deg(double angle)
{
	return (angle * 180 / M_PI);
}

inline int32_t	get_y_pos(int32_t map_height, double dev_y)
{
	return (map_height - 1 - (int32_t)floor(dev_y));
}
