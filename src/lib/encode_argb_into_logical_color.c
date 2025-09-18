/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_argb_into_logical_color.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:03:43 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 15:34:40 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int32_t	encode_argb_into_logical_color(t_argb argb)
{
	return ((int32_t)argb.a << 24 | (int32_t)argb.r << 16
		| (int32_t)argb.g << 8 | (int32_t)argb.b);

}
