/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:07:58 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 16:30:35 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

#include "loop.h"

double	get_time(t_time_precision time_precision)
{
	struct timeval	sys_raw_time;
	double			time;

	gettimeofday(&sys_raw_time, NULL);
	time = (sys_raw_time.tv_sec * 1e6) + sys_raw_time.tv_usec;
	if (time_precision == T_MICROSECOND)
		return (time);
	else if (time_precision == T_MILISECOND)
		return (time / 1e3);
	else
		return (time / 1e6);
}
