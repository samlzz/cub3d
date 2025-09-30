/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:10:02 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 17:28:42 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef CUB3D_BONUS

# include <stdint.h>
# include <stdlib.h>

# include "data/init_err.h"
# include "data/sprite.h"
# include "ft_mlx/ft_mlx_texture.h"
# include "libft.h"
# include "cubmap.h"
# include "mlx.h"
# include "data.h"
# include "vec/vec.h"
# include "window.h"

static void	_fatal_clear_mlx(t_mlx *mlx)
{
	mlx_do_key_autorepeaton(mlx->display);
	if (mlx->display && mlx->game.image_ptr)
		mlx_destroy_image(mlx->display, mlx->game.image_ptr);
	if (mlx->minimap.image_ptr)
		mlx_destroy_image(mlx->display, mlx->minimap.image_ptr);
	if (mlx->window)
		mlx_destroy_window(mlx->display,
			mlx->window);
	mlx_destroy_display(mlx->display);
	free(mlx->display);
	ft_bzero(mlx, sizeof (t_mlx));
}

void	data_init(t_data *data)
{
	if (install_mlx(
			&data->mlx,
			(t_vec2i){WIN_WIDTH, WIN_HEIGHT},
		&data->inputs.cursor,
		data->map.g.dim
	))
		data_exit(data, IE_MLX_INIT_ERROR);
	if (install_doors(&data->map.g, &data->map.doors))
		data_exit(data, IE_INSTALLING_DOOR_FAILURE);
	if (ft_mlx_textures_load_list(data->map.textures, TEX__COUNT, &data->mlx)
		|| install_sprites_bank(&data->map.bank, &data->mlx))
		data_exit(data, IE_OPEN_TEXTURE_FAILURE);
	install_hooks(data);
	install_frame_engine(data);
	camera_init(&data->camera, data->map.g);
}

void	data_exit(t_data *data, t_init_error code)
{
	uninstall_doors(&data->map.doors);
	clear_sprite_bank(&data->map.bank, &data->mlx);
	free_map(&data->map, &data->mlx);
	_fatal_clear_mlx(&data->mlx);
	exit(ie_print_err(code));
}

#endif
