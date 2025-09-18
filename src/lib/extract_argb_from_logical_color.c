/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_argb_from_logical_color.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:31:52 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 15:32:02 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_argb	extract_argb_from_logical_color(int32_t logical_color)
{
	t_argb	argb;

	argb.a = (uint8_t)((logical_color & 0xFF000000) >> 24);
	argb.r = (uint8_t)((logical_color & 0x00FF0000) >> 16);
	argb.g = (uint8_t)((logical_color & 0x0000FF00) >> 8);
	argb.b = (uint8_t)(logical_color & 0x000000FF);
	return (argb);
}
