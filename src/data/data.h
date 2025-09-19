/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:16:51 by eazard            #+#    #+#             */
/*   Updated: 2025/09/19 12:50:41 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <stdbool.h>
# include <stdint.h>

# include "camera.h"
# include "cubmap.h"

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT	700
# endif
# ifndef WIN_WIDTH
#  define WIN_WIDTH		1100
# endif
# ifndef WIN_NAME
#  define WIN_NAME		"cub3d"
# endif
# ifndef FOV_FACTOR
#  define FOV_FACTOR		0.66
# endif

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
#  define KEY_ESC    53
#  define KEY_W      13
#  define KEY_A      0
#  define KEY_S      1
#  define KEY_D      2
#  define KEY_LEFT   123
#  define KEY_RIGHT  124
*/
# endif

typedef struct s_img	t_img;
typedef struct s_inputs	t_inputs;
typedef struct s_mlx	t_mlx;
typedef struct s_data	t_data;
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
	EC_SUCCESS,
	EC_DESTROY_NOTIFY,
	EC_MLX_INIT_ERROR,
	EC_DDA_RAYDIR_VEC_ZERO,
	EC_OPEN_TEXTURE_FAILURE,
};

void	data_init(t_data *data);

void	clear_data(t_data *data, bool fatal, int16_t exit_code);

// * Install

int16_t	install_mlx(t_mlx *mlx, t_vec2i screen);
int16_t	install_mlx_img(t_mlx *mlx, t_img *img, t_vec2i screen_dim);

void	install_hooks(t_data *data);

void	install_frame_engine(t_data *data);
int16_t	load_cardinal_textures(t_map *map, t_img cardinal_textures[],
			t_mlx *mlx);
void	fatal_clear_cardinal_textures(t_mlx *mlx, t_img cardinal_textures[]);

#endif