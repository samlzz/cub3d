/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_update_doors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:45:16 by eazard            #+#    #+#             */
/*   Updated: 2025/09/26 18:10:25 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data/data.h"
#include "door.h"
#include "vec/ftmath_utils.h"

void	_update_opening_door(t_door *door)
{
	door->openness += (time_delta_between_frame / DOOR_TIME_TO_OPEN);
	door->openness = ftm_clamp(door->openness, 0.0, 1.0);
	if (door->openness == 1.0)
		door->state = DOOR_OPENED;
}

void	_update_closing_door(t_door *door)
{
	door->openness -= (time_delta_between_frame / DOOR_TIME_TO_OPEN);
	door->openness = ftm_clamp(door->openness, 0.0, 1.0);
	if (door->openness == 0.0)
		door->state = DOOR_CLOSED;
}

void	old_update_doors(t_door **doors, double time_delta_between_frame)
{
	t_vec2i	index;
	t_door	*door;

	index.y = 0;
	while (doors[index.y])
	{
		index.x = 0;
		door = &doors[index.y][index.x];
		while (door->state != DOOR_END_OF_DOOR_ROW)
		{
			if (door->state != DOOR_NO_DOOR)
			{
				if (door->state == DOOR_OPENING)
					_update_opening_door(&door, time_delta_between_frame);
				if (door->state == DOOR_CLOSING)
					_update_closing_door(&door, time_delta_between_frame);
			}
			index.x++;
			door = &doors[index.y][index.x];
		}
		index.y++;
	}
}
