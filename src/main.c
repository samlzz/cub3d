/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:34:03 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/18 15:02:11 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>

#include "data/camera.h"
#include "mlx.h"
#include "libft.h"
#include "error.h"
#include "data/data.h"
#include "parsing/parser.h"
#include "test/test.h"

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
	mlx_loop(data.mlx.display);
	clear_data(&data, true, EC_SUCCESS);
	return (0);
}
