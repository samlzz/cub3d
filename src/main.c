/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:34:03 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/18 09:27:37 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "cub3d.h"

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

int	cub3d_main(int32_t ac, char *av[])
{
	t_data	data;
	int16_t	code;

	if (ac != 2 || !is_dot_cub(av[1]))
		return (ft_putendl_fd(ERR_WRONG_USAGE, 2), 2);
	ft_memset(&data, 0, sizeof(data));
	code = parse_cub(av[1], &data.map);
	if (code)
		return (code);
	print_map(&data.map);
	data_init(&data);
	// show_cardinal_textures(&data.mlx, data.assets.cardinal_textures);
	mlx_loop(data.mlx.display);
	clear_data(&data, true, SUCCESS);
	return (0);
}


int	test_parsing(int ac, char **av)
{
	int16_t	code;
	t_map	map;

	if (ac != 2 || !is_dot_cub(av[1]))
		return (ft_putendl_fd(ERR_WRONG_USAGE, 2), 2);
	ft_bzero(&map, sizeof(t_map));
	code = parse_cub(av[1], &map);
	if (code)
		return (code);
	print_map(&map);
	return (0);
}

int	main(int32_t ac, char *av[])
{
	// (void)ac; (void)av;
	return (cub3d_main(ac, av));
	// return (test_parsing(ac, av));
	// test_get_time();
	// return (0);
}
