/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:16:51 by eazard            #+#    #+#             */
/*   Updated: 2025/09/09 11:56:30 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "mlx.h"

# include "cub3d.h"

# define WINDOW_HEIGHT 600
# define WINDOW_WIDTH 800

/* keys.h — keycodes Linux/X11 pour minilibx-linux */
#pragma once

#ifdef __linux__
# define KEY_ESC    65307
# define KEY_W      119
# define KEY_A      97
# define KEY_S      115
# define KEY_D      100
# define KEY_LEFT   65361
# define KEY_RIGHT  65363
#else
/* macOS (si besoin) :
# define KEY_ESC    53
# define KEY_W      13
# define KEY_A      0
# define KEY_S      1
# define KEY_D      2
# define KEY_LEFT   123
# define KEY_RIGHT  124
*/
#endif


typedef struct s_data	t_data;
typedef struct s_mlx	t_mlx;
typedef struct s_img	t_img;
typedef struct s_inputs	t_inputs;

struct s_img
{
	void	*image;
	int8_t	*data_addr;
	int32_t	bpp;
	int32_t	endian;
	int32_t	line_len;
};

struct s_inputs
{
	bool	forward;
	bool	backward;
	bool	left;
	bool	right;
	bool	turn_left;
	bool	turn_right;
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
	t_inputs	inputs;
};

enum	exit_code
{
	SUCCESS,
	DESTROY_NOTIFY,
	MLX_INIT_ERROR,
};

void	data_init(t_data *data);
void	start_mlx(t_data *data);
void	install_hooks(t_data *data);
void	install_frame_engine(t_data *data);
void	clear_data(t_data *data, bool fatal, int16_t exit_code);

#endif