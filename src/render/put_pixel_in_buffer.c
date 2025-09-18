/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_in_buffer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:25:30 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 16:31:13 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	put_pixel_in_buffer(t_img *img, int x, int y, int32_t color)
{
	if ((unsigned)x >= WINDOW_WIDTH || (unsigned)y >= WINDOW_HEIGHT) return;
    char *dst;
	
	dst = (char *)(img->data_addr + y * img->line_len + x * (img->bpp / 8));
    *(uint32_t *)dst = color;
}
