/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:17:57 by eazard            #+#    #+#             */
/*   Updated: 2025/09/10 10:32:04 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"



void	data_init(t_data *data)
{
	install_mlx(data);
	install_hooks(data);
	install_frame_engine(data);
	game_data_init(data);
}
