/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:23:12 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/04 15:47:46 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <stddef.h>
# include <stdint.h>

struct s_vec2i
{
	int32_t	x;
	int32_t	y;
};
typedef struct s_vec2i		t_vec2i;

enum e_directions
{
	DIR_N,
	DIR_S,
	DIR_E,
	DIR_W,
	DIR_MAX
};
typedef enum e_directions	t_directions;

struct s_vec2d
{
	double	x;
	double	y;
};
typedef struct s_vec2d		t_vec2d;

#endif
