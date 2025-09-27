/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmath_comp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:52:48 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/27 13:24:26 by sliziard         ###   ########.fr       */
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
