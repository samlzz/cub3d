/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:41:20 by eazard            #+#    #+#             */
/*   Updated: 2025/09/15 11:31:01 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	draw_vline(t_data *data, t_line line, uint32_t color)
{
	int	y;

	y = line.y0;
	while (y < line.y1)
	{
		put_pixel_in_buffer(&data->mlx.img, line.column, y, color);
		y++;
	}
}