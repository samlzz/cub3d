/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal_clear_doors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:35:07 by eazard            #+#    #+#             */
/*   Updated: 2025/09/26 18:09:13 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "door.h"

void	fatal_clear_doors(t_door ***doors)
{
	size_t	i;

	if (*doors)
	{
		i = 0;
		while ((*doors)[i])
		{
			free((*doors)[i]);
			(*doors)[i] = NULL;
			i++;
		}
		free(*doors);
		(*doors) = NULL;
	}
}
