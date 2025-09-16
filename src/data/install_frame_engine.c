/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   install_frame_engine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:30:26 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 16:48:30 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "data.h"
#include "loop/loop.h"

void	install_frame_engine(t_data *data)
{
	(void)data; //to delete
	mlx_loop_hook(data->mlx.display, &app_loop_hook, data);
}
