/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:16:51 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 13:40:57 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <stdbool.h>
# include <stdint.h>

# include "cubmap.h"
# include "camera.h"
# include "window.h"

# ifdef __linux__

#  define KEY_ESC			65307
#  define KEY_W				119
#  define KEY_A				97
#  define KEY_S				115
#  define KEY_D				100
#  define KEY_LEFT			65361
#  define KEY_RIGHT			65363
#  define KEY_E				101
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

typedef struct s_img		t_img;

typedef struct s_mouse		t_mouse;
typedef struct s_inputs		t_inputs;
typedef struct s_mlx		t_mlx;
typedef struct s_data		t_data;
typedef enum e_init_error	t_init_error;

struct s_mouse
{
	t_vec2i	pos;
	double	dx_accum;
	bool	pending_recenter;
	bool	hidden;
};

struct s_inputs
{
	bool	forward;
	bool	backward;
	bool	left;
	bool	right;
	bool	turn_left;
	bool	turn_right;
	bool	try_to_interact_with_door;
	t_mouse	cursor;
};

struct s_mlx
{
	void	*window;
	void	*display;
	t_img	game;
	t_img	minimap;
	t_vec2i	minimap_pos;
};

struct s_data
{
	t_camera	camera;
	t_mlx		mlx;
	t_inputs	inputs;
	t_map		map;
	double		zbuf[WIN_WIDTH];
};

enum e_init_error
{
	EC_SUCCESS,
	EC_DESTROY_NOTIFY,
	EC_MLX_INIT_ERROR,
	EC_DDA_RAYDIR_VEC_ZERO,
	EC_OPEN_TEXTURE_FAILURE,
	EC_INSTALLING_DOOR_FAILURE,
};

void	data_init(t_data *data);
void	data_exit(t_data *data, t_init_error code);

// * Install

int16_t	install_mlx(t_mlx *mlx, t_vec2i screen, t_mouse *cursor, t_vec2i grid);
int16_t	install_mlx_img(t_mlx *mlx, t_img *img, t_vec2i img_dim);

void	install_hooks(t_data *data);

void	install_frame_engine(t_data *data);

int16_t	install_doors(t_grid *grid, t_door ***doors);
void	uninstall_doors(t_door ***doors);

#endif