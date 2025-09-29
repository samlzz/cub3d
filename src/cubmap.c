/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:02:44 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/28 19:24:06 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

#include "cubmap.h"
#include "ft_mlx/ft_mlx_texture.h"
#include "libft.h"

static void	_ft_free(void **ptr)
{
	if (!ptr || !*ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}

void	free_grid(t_grid *g)
{
	if (!g || !g->grid)
		return ;
	ft_splitfree(g->grid, g->dim.y);
}

void	free_map(t_map *m, t_mlx *mlx)
{
	int32_t	i;

	if (!m)
		return ;
	i = 0;
	while (i < TEX__COUNT)
	{
		_ft_free((void **)&m->textures[i].path);
		ft_mlx_texture_destroy(m->textures + i, mlx);
		i++;
	}
	free_grid(&m->g);
}
