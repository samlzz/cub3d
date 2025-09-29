/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:34:03 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/28 19:34:09 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>

#include "cubmap.h"
#include "data/camera.h"
#include "mlx.h"
#include "libft.h"
#include "data/data.h"
#include "parsing/parser.h"
#include "test/test.h"

#define ERR_WRONG_USAGE "Usage: ./cub3d <path_to_map_file>.cub"

void	show_cardinal_textures(t_mlx *mlx, t_img cardinal_textures[])
{
	int	i;

	i = 0;
	while (i < DIR_MAX)
	{
		if (i > 0)
			sleep(1);
		mlx_put_image_to_window(mlx->display, mlx->window,
			cardinal_textures[i].image_ptr, 0, 0);
		i++;
	}
}

int	main(int32_t ac, char *av[])
{
	int16_t	code;
	t_data	data;

	if (ac != 2 || !is_dot_cub(av[1]))
		return (ft_putendl_fd(ERR_WRONG_USAGE, 2), 2);
	ft_bzero(&data, sizeof (t_data));
	code = parse_cub(av[1], &data.map);
	if (code)
		return (free_map(&data.map, &data.mlx), code);
	print_map(&data.map);
	data_init(&data);
	// show_cardinal_textures(&data.mlx, data.assets.cardinal_textures);
	mlx_loop(data.mlx.display);
	data_exit(&data, EC_SUCCESS);
	return (0);
}
