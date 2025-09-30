/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:34:03 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 18:05:06 by sliziard         ###   ########.fr       */
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

#define ERR_WRONG_USAGE "Usage: ./cub3d <path_to_map_file>.cub"

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
	data_init(&data);
	mlx_loop(data.mlx.display);
	data_exit(&data, IE_SUCCESS);
	return (0);
}
