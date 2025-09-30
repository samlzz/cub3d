/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:50:19 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 14:21:15 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include <stdint.h>

# include "color.h"
# include "data/data.h"
# include "ft_mlx/ft_mlx_img.h"
# include "data/camera.h"

# ifndef MINIMAP_SCALE
#  define MINIMAP_SCALE			12
# endif
# ifndef MINIMAP_RADIUS
#  define MINIMAP_RADIUS		8
# endif
# ifndef MINIMAP_BORDER_PX
#  define MINIMAP_BORDER_PX 	3
# endif
# ifndef MINIMAP_BORDER_COLOR
#  define MINIMAP_BORDER_COLOR	C_WHITE
# endif

# ifndef MINIMAP_PLAYER_RADIUS
#  define MINIMAP_PLAYER_RADIUS	4
# endif
# define MINIMAP_ARROW_DEPTH	1.2
# define MINIMAP_ARROW_LEN		0.4
# define MINIMAP_ARROW_WIDTH	0.5
# define MINIMAP_ARROW_THICK	3

# define MINIMAP_ARROW_BORDER	0

typedef struct s_arrow_len	t_arrow_len;
typedef struct s_border 	t_border;

struct s_arrow_len
{
	double arrow_depth;
	double head_len;
	double head_wid;
};

struct s_border
{
	int32_t	px;
	t_color	color;
};

void	render_minimap(t_mlx *mlx, const t_grid *grid, const t_camera *cam);
void		render_minimap_player(t_img *minimap, t_vec2i start,
				int32_t grid_height, const t_camera *cam);

t_vec2iv3	arrow_triangle_build(t_vec2i player, t_vec2d u, t_arrow_len L);
void		arrow_triangle_draw(t_img *minimap, t_vec2iv3 tri, t_color fill, t_border border);

#endif
