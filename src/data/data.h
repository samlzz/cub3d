/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:16:51 by eazard            #+#    #+#             */
/*   Updated: 2025/09/17 20:14:55 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <stdbool.h>
# include <stdint.h>

# include "camera.h"
# include "cubmap.h"

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT	1080
# endif
# ifndef WIN_WIDTH
#  define WIN_WIDTH		1920
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
	struct s_camera	camera;
	t_mlx			mlx;
	t_inputs		inputs;
	t_map			map;
};

enum e_exit_code
{
	SUCCESS,
	DESTROY_NOTIFY,
	MLX_INIT_ERROR,
	DDA_RAYDIR_VEC_ZERO,
};

void	data_init(t_data *data);

void	clear_data(t_data *data, bool fatal, int16_t exit_code);

// * Install

int16_t	install_mlx(t_mlx *mlx, t_vec2i screen);
int16_t	install_mlx_img(t_mlx *mlx, t_img *img, t_vec2i screen_dim);

void	install_hooks(t_data *data);

void	install_frame_engine(t_data *data);

#endif