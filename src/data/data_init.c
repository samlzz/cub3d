/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:17:57 by eazard            #+#    #+#             */
/*   Updated: 2025/09/08 16:30:13 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void	data_init(t_data *data)
{
	// game_data_init(data); // needed ?
	start_mlx(data);
	install_hooks(data);
	install_frame_engine(data);
}
