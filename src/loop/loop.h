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

#ifndef LOOP_H
# define LOOP_H

# include "vec/vec.h"
# include "data/data.h"

# define MOVE_SPEED 3.0
# define ROT_SPEED 2.0

# define PLAYER_RADIUS 0.20
# define EPS 1e-9

typedef enum e_time_precision		t_time_precision;

enum e_time_precision
{
	T_SECOND,
	T_MILISECOND,
	T_MICROSECOND,
};

double	get_time(t_time_precision time_precision);
int		app_update(t_data *data, double time_delta_beetwen_frame);
int		app_loop_hook(t_data *data);
void	clamp_move_try_length(t_vec2d *move_try,
			double time_delta_beetwen_frame);
void	try_move_and_update_pos(t_data *data, t_vec2d move_try);
int		row_from_worldY(const t_data *data, double y);


#endif