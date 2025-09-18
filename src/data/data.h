/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:16:51 by eazard            #+#    #+#             */
/*   Updated: 2025/09/18 09:13:32 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "mlx.h"

# include "cub3d.h"
# include "cubmap.h"
# include "camera.h"

# define WINDOW_HEIGHT 600
# define WINDOW_WIDTH 800

/* keys.h — keycodes Linux/X11 pour minilibx-linux */
# pragma once

# ifdef __linux__
#  define KEY_ESC    65307
#  define KEY_W      119
#  define KEY_A      97
#  define KEY_S      115
#  define KEY_D      100
#  define KEY_LEFT   65361
#  define KEY_RIGHT  65363
#  define E_DESTROY_NOTIFY -1
# else
/* macOS (si besoin) :
# define KEY_ESC    53
# define KEY_W      13
# define KEY_A      0
# define KEY_S      1
# define KEY_D      2
# define KEY_LEFT   123
# define KEY_RIGHT  124
*/
# endif

# define FOV_FACTOR 0.66

typedef struct s_camera	t_camera;
typedef struct s_data	t_data;
typedef struct s_mlx	t_mlx;
typedef struct s_img	t_img;
typedef struct s_inputs	t_inputs;
typedef struct s_map	t_map;
typedef struct s_assets	t_assets;

struct s_img
{
	void	*image_ptr;
	char	*data_addr;
	int32_t	bpp;
	int32_t	endian;
	int32_t	line_len;
	int32_t	width;
	int32_t	height;
};

struct s_assets
{
	t_img	cardinal_textures[DIR_MAX];
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
	struct s_camera	camera;
	t_mlx			mlx;
	t_inputs		inputs;
	t_map			map;
	t_assets		assets;
};

enum e_exit_code
{
	SUCCESS,
	DESTROY_NOTIFY,
	MLX_INIT_ERROR,
	DDA_RAYDIR_VEC_ZERO,
	OPEN_TEXTURE_FAILURE,
};

void	data_init(t_data *data);
void	install_mlx(t_data *data);
void	install_hooks(t_data *data);
void	install_frame_engine(t_data *data);
void	game_data_init(t_data *data);
void	clear_data(t_data *data, bool fatal, int16_t exit_code);
void	game_camera_init(t_data *data);
void	set_up_camera_dir_and_plane(t_data *data, char direction);
int16_t	load_cardinal_textures(t_map *map, t_img cardinal_textures[],
			t_mlx *mlx);
void	clear_cardinal_textures(t_mlx *mlx, t_img cardinal_textures[],
			bool fatal);

#endif