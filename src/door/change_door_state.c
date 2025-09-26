/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_door_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:21:19 by eazard            #+#    #+#             */
/*   Updated: 2025/09/26 18:11:26 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door.h"

void	change_door_state(t_door *door)
{
	if (door->state == DOOR_CLOSED)
		door->state = DOOR_OPENED;
	else if (door->state == DOOR_OPENED)
		door->state = DOOR_CLOSED;
}
