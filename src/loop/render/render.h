/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:31:34 by eazard            #+#    #+#             */
/*   Updated: 2025/09/29 19:01:04 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <stdbool.h>
# include <stdint.h>

# include "vec/vec.h"
# include "data/data.h"

# define BIG 1e30
# define FOG_DENSITY 0.1
# define FOG_COLOR BLACK

typedef struct s_img		t_img;
typedef struct s_ddaline	t_ddaline;
typedef struct s_dda_data	t_dda_data;
typedef struct s_asset_data	t_asset_data;

struct s_ddaline
{
	int	column;
	int	y0;
	int	y1;
};

struct s_dda_data
{
	t_vec2d			map;
	t_vec2d			delta_dist;
	t_vec2d			step;
	t_vec2d			side_dist;
	t_vec2d			ray_dir;
	int32_t			line_height;
	int32_t			draw_start;
	int32_t			draw_end;
	double			perp_wall_dist;
	bool			side;
	t_ddaline		line;
	int32_t			x;
	double			wall_x;	
	int32_t			tex_x;	
	t_directions	wall_orientation;
	double			tex_step;
	double			tex_pos;
	int32_t			tex_y;
	int32_t			y;
	t_img			*tex_img;
	uint32_t		color;
	char			target;
};

struct s_asset_data
{
	int32_t	i;
	int32_t	printed_sprit_index;
	t_vec2d	camera_space_coordinate;
	int32_t	sprite_center_x_screen_space;
	int32_t	sprite_height;
	int32_t	sprite_width;
	t_vec2i	left_bound;
	t_vec2i	right_bound;
	t_img	frame_asset_img;
	int32_t	frame_index;
};

t_vec2d	get_ray_dir(t_camera *cam, int32_t x);
void	render_frame(t_data *data);

// *DDA
void	init_dda(t_data *data, t_dda_data *dda);
void	dda_loop(t_data *data, t_dda_data *dda);
void	dda_algorithm(t_data *data, t_dda_data *dda);

/* deduce_after_loop */
void	deduce_perp_wall_dist(t_data *data, t_dda_data *dda);
void	deduce_wall_band_size(t_data *data, t_dda_data *dda);
void	deduce_wall_orientation(t_dda_data *dda);
void	deduce_wall_x(t_data *data, t_dda_data *dda);
void	deduce_texture_related_data(t_data *data, t_dda_data *dda);

// Draw
void	draw_clear(t_img *img, uint32_t ceil_color, uint32_t floor_color);
void	draw_bend_with_textue(t_data *data, t_dda_data *dda);

#endif