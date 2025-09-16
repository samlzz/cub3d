/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_from_worldY.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:33:20 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 16:31:12 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

int	row_from_worldY(const t_data *data, double y)
{
	return (data->map.g.dim.y - 1 - (int)floor(y));
}
