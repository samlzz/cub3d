/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bank.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:23:50 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 16:52:48 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef CUB3D_BONUS

# include <stdio.h>
# include <stdlib.h>

# include "libft.h"
# include "../sprite.h"

void	clear_sprite_bank(t_sprites_data *bank, t_mlx *mlx)
{
	size_t	i;

	if (bank->sprites)
	{
		i = 0;
		while (i < bank->count)
			sprite_free(bank->sprites[i++], mlx);
	}
	free(bank->square_distances);
	free(bank->order);
	free(bank->sprites);
}

int16_t	install_sprites_bank(t_sprites_data *bank, t_mlx *mlx)
{
	const t_sprite_meta	*defs;
	size_t				i;
	size_t				sprites_nb;

	defs = sprites_get_metadata(&sprites_nb);
	bank->square_distances = ft_calloc(sprites_nb, sizeof (double));
	bank->order = ft_calloc(sprites_nb, sizeof (int32_t));
	bank->sprites = ft_calloc(sprites_nb, sizeof (t_sprite));
	if (!bank->square_distances || !bank->order || !bank->sprites)
		return (perror("cub3d: install_sprites_bank: malloc"),
			free(bank->square_distances),
			free(bank->order),
			free(bank->sprites), 1);
	bank->count = sprites_nb;
	i = 0;
	while (i < sprites_nb)
	{
		bank->sprites[i].name = defs[i].name;
		bank->sprites[i].pos = defs[i].default_pos;
		if (sprite_load(bank->sprites + i, defs[i].paths, mlx))
			return (bank->count = i, clear_sprite_bank(bank, mlx), 1);
		i++;
	}
	return (0);
}

#endif