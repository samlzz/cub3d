/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmath_comp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:52:48 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 16:01:46 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int32_t	ftm_min(int32_t a, int32_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int32_t	ftm_min3(int32_t a, int32_t b, int32_t c)
{
	return (ftm_min(a, ftm_min(b, c)));
}

int32_t	ftm_max(int32_t a, int32_t b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int32_t	ftm_max3(int32_t a, int32_t b, int32_t c)
{
	return (ftm_max(a, ftm_max(b, c)));
}
