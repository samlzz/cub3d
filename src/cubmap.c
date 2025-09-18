/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:17:57 by eazard            #+#    #+#             */
/*   Updated: 2025/09/18 15:17:26 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"



void	free_map(t_map *m)
{
	install_mlx(data);
	install_hooks(data);
	install_frame_engine(data);
	game_data_init(data);
}
