/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:14:54 by eazard            #+#    #+#             */
/*   Updated: 2025/09/08 16:40:47 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "untextured_raycasting.h"

int	app_loop_hook(t_data *data)
{
	long	time_in_ms;

	time_in_ms = get_tine(T_MILISECOND);
	return (0);
}

int	app_update(void)
{
	;
}

long	get_time(t_time_precision time_precision)
{
	struct timeval	sys_raw_time;
	long			our_clean_time;
	long			divider;

	gettimeofday(&sys_raw_time, NULL);
	our_clean_time = sys_raw_time.tv_sec * 1e6 + sys_raw_time.tv_usec;
	if (time_precision == T_MICROSECOND)
		return (our_clean_time);
	else if (time_precision == T_SECOND)
		divider = 1e6;
	else if (time_precision == T_MILISECOND)
		divider = 1e3;
	else
		divider = 1;
	return (our_clean_time / divider);
}
