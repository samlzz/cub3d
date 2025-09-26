/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   install_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:13:13 by eazard            #+#    #+#             */
/*   Updated: 2025/09/26 18:09:54 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door.h"
#include "cubmap.h"
#include "libft.h"

static void	_fill_row(t_door *doors_row, char *grid_row)
{
	size_t	i;

	i = 0;
	while (grid_row[i])
	{
		if (grid_row[i] == 'D')
			doors_row[i].state = DOOR_CLOSED;
		else
			doors_row[i].state = DOOR_NO_DOOR;
		i++;
	}
	doors_row[i].state = DOOR_END_OF_DOOR_ROW;
}

/*
install another grid in the t_map structure
in witch each case in door grid has its coresponding case in map grid
if the case in map grid contain NO 'D' => then the case in door case
										  has a state of DOOR_NO_DOOR
if the case in map grid contain 'D' => then the case in door case
									   has a state DIFFERENT from DOOR_NO_DOOR
*/
int16_t	install_doors(t_grid *grid, t_door ***doors)
{
	int32_t	i;
	int32_t	row_len;

	i = 0;
	(*doors) = ft_calloc(sizeof(t_door *), grid->dim.y + 1);
	if (!(*doors))
		return (1);
	while (i < grid->dim.y)
	{
		row_len = ft_strlen(grid->grid[i]);
		(*doors)[i] = ft_calloc(sizeof(t_door), row_len + 1);
		if (!(*doors)[i])
			return (1);
		_fill_row((*doors)[i], grid->grid[i]);
		i++;
	}
	return (0);
}
