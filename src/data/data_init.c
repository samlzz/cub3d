/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:17:57 by eazard            #+#    #+#             */
/*   Updated: 2025/09/18 09:15:49 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void	data_init(t_data *data)
{
	install_mlx(data);
	install_hooks(data);
	install_frame_engine(data);
	if (load_cardinal_textures(&data->map, data->assets.cardinal_textures,
			&data->mlx) != SUCCESS)
		clear_data(data, true, OPEN_TEXTURE_FAILURE);
	game_data_init(data);
}
