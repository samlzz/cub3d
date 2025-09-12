/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_from_worldY.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:33:20 by eazard            #+#    #+#             */
/*   Updated: 2025/09/12 11:34:14 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

int	row_from_worldY(const t_data *data, double y)
{
    return (data->map.dimensions.y - 1 - (int)floor(y));
}
