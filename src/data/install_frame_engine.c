/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   install_frame_engine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:30:26 by eazard            #+#    #+#             */
/*   Updated: 2025/09/08 16:32:28 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "untextured_raycasting.h"

void	install_frame_engine(t_data *data)
{
	mlx_loop_hook(data->mlx.display, &app_loop_hook, data);
}