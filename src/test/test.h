/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:50:47 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 16:22:16 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

// *Forward declaration

typedef struct s_camera	t_camera;
typedef struct s_map	t_map;
typedef struct s_grid	t_grid;

// *Debug

# ifndef UNTEXTURED_RAYCASTING_DEBUG
#  define UNTEXTURED_RAYCASTING_DEBUG 0
# endif

// *Functions
/*camera*/
void	test_camera_rotation(void);
void	test_get_time(void);

/*map*/
void	print_grid(const t_grid *g);
void	print_map(const t_map *m);

#endif
