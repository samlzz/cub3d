/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:34:03 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/18 15:22:15 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>

#include "data/camera.h"
#include "mlx.h"
#include "libft.h"
#include "error.h"
#include "data/data.h"
#include "parsing/parser.h"
#include "test/test.h"

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
		return (parse_err_print(code, &data.map), code);
	print_map(&data.map);
	data_init(&data);
	// show_cardinal_textures(&data.mlx, data.assets.cardinal_textures);
	mlx_loop(data.mlx.display);
	clear_data(&data, true, EC_SUCCESS);
	return (0);
}
