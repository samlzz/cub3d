/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:30:55 by eazard            #+#    #+#             */
/*   Updated: 2025/09/26 18:07:31 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOORS_H
# define DOORS_H

// # define DOOR_TIME_TO_OPEN 0.7
# define DOOR_DISTANCE_TO_BE_ABLE_TO_INTERACT 1.5

# include <stdbool.h>

# include "cubmap.h"
# include "vec/vec.h"

typedef enum e_door_state	t_door_state;
typedef struct s_grid		t_grid;
typedef struct s_door		t_door;

enum e_door_state
{
	DOOR_NO_DOOR,
	DOOR_CLOSED,
	DOOR_OPENED,
	DOOR_END_OF_DOOR_ROW,
};

struct	s_door
{
	t_door_state	state;
};

void	update_doors(t_door **doors, double time_delta_between_frame);
void	fatal_clear_doors(t_door ***doors);
int16_t	install_doors(t_grid *grid, t_door ***doors);
void	change_door_state(t_door *door);

#endif