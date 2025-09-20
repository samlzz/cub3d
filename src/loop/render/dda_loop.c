/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:54:47 by eazard            #+#    #+#             */
/*   Updated: 2025/09/20 15:13:52 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "vec/ftmath_utils.h"

static bool	wall_has_been_hit(t_data *data, t_dda_data *dda)
{
	char	cell;
	t_vec2i	cubpos;

	cubpos.y = get_y_pos(data->map.g.dim.y, dda->map.y);
	if (cubpos.y < 0 || cubpos.y >= data->map.g.dim.y)
		return (true);
	cubpos.x = (int32_t)dda->map.x;
	if (cubpos.x < 0 || cubpos.x >= data->map.g.dim.x)
		return (true);
	cell = data->map.g.grid[cubpos.y][cubpos.x];
	if (cell == '1')
		return (true);
	return (false);
}

void	dda_loop(t_data *data, t_dda_data *dda)
{
	while (wall_has_been_hit(data, dda) == false)
	{
		if (dda->side_dist.x < dda->side_dist.y)
		{
			dda->side_dist.x += dda->delta_dist.x;
			dda->map.x += dda->step.x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist.y += dda->delta_dist.y;
			dda->map.y += dda->step.y;
			dda->side = 1;
		}
	}
}
