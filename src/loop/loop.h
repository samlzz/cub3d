/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:13:04 by eazard            #+#    #+#             */
/*   Updated: 2025/09/09 11:56:17 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNTEXTURED_RAYCASTING_H
# define UNTEXTURED_RAYCASTING_H

# include <sys/time.h>

# include "cub3d.h"

# define MOVE_SPEED 3.0
# define ROT_SPEED 2.0

typedef enum e_time_precision		t_time_precision;
typedef struct s_data				t_data;

enum e_time_precision
{
	T_SECOND,
	T_MILISECOND,
	T_MICROSECOND,
};

double	get_time(t_time_precision time_precision);
int		app_update(t_data *data, double time_delta_beetwen_frame);
int		app_loop_hook(t_data *data);


#endif