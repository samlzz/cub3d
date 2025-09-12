/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:41:20 by eazard            #+#    #+#             */
/*   Updated: 2025/09/12 15:33:37 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	draw_vline(t_data *data, t_line line, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		if (y >= line.y0 && y < line.y1)
		{
			while (x < WINDOW_WIDTH)
			{
				if (x == line.column)
				{
					put_pixel_in_buffer(&data->mlx.img, x, y, color);
					x = WINDOW_WIDTH;
				}
				x++;
			}
		}
		y++;
	}
}