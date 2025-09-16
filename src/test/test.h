/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:50:47 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 15:54:24 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include "cub3d.h"

typedef struct s_camera	t_camera;
typedef struct s_map	t_map;


/*camera*/
void	test_camera_rotation(void);
void	test_get_time(void);

/*map*/
void	print_grid(const t_grid *g);
void	print_map(const t_map *m);

#endif
