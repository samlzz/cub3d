/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmath_conversions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:08:23 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/26 22:16:33 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath_utils.h"

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
