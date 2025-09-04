/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertion_deg_rad.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:16:40 by eazard            #+#    #+#             */
/*   Updated: 2025/09/04 17:18:47 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

inline double	deg_to_rad(double angle)
{
	return (angle * M_PI / 180);
}

inline double	rad_to_deg(double angle)
{
	return (angle * 180 / M_PI);
}
