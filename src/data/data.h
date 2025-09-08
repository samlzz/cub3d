/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:16:51 by eazard            #+#    #+#             */
/*   Updated: 2025/09/08 15:03:22 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "mlx.h"

# include "cub3d.h"

# define WINDOW_HEIGHT 800
# define WINDOW_WIDTH 600

typedef struct s_data	t_data;
typedef struct s_mlx	t_mlx;
typedef struct s_img	t_img;

struct s_img
{
	void	*image;
	int8_t	*data_addr;
	int32_t	bpp;
	int32_t	endian;
	int32_t	line_len;
};

struct s_mlx
{
	void	*window;
	void	*display;
	t_img	img;
};

struct s_data
{
	t_camera	camera;
	t_mlx		mlx;
};

enum	exit_code
{
	SUCCESS,
	MLX_INIT_ERROR,
};

void	data_init(t_data *data);
void	cub3d_mlx_init(t_data *data);
void	clear_data(t_data *data, bool fatal, int16_t exit_code);

#endif