/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_in_buffer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:25:30 by eazard            #+#    #+#             */
/*   Updated: 2025/09/12 14:28:10 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	put_pixel_in_buffer(t_img *img, int x, int y, int color)
{
	*(img->data_addr + y * img->line_len + x * img->bpp / 8) = color;
}
