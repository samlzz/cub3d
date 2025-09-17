/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:31:34 by eazard            #+#    #+#             */
/*   Updated: 2025/09/17 16:55:02 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <stdbool.h>

# include "vec/vec.h"
# include "data/data.h"

# define BIG 1e30

typedef struct s_line		t_line;
typedef struct s_dda_data	t_dda_data;

struct s_line
{
	int	column;
	int	y0;
	int	y1;
};

struct s_dda_data
{
	t_vec2d	map;
	t_vec2d	delta_dist;
	t_vec2d	step;
	t_vec2d	side_dist;
	t_vec2d	ray_dir;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	perp_wall_dist;
	bool	side;
	t_line	line;
	int		x;
};

// DDA algo
void	render_frame(t_data *data);
void	init_dda(t_data *data, t_dda_data *dda);
void	dda_algorithm(t_data *data, t_dda_data *dda);

// Draw
void	draw_clear(t_img *img, uint32_t ceil_color, uint32_t floor_color);
void	draw_vline(t_data *data, t_line line, uint32_t color);

#endif