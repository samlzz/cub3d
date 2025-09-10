/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:50:47 by eazard            #+#    #+#             */
/*   Updated: 2025/09/10 12:20:52 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include "cub3d.h"

typedef struct s_map	t_map;


/*camera*/
void	test_camera_rotation(void);
void	test_get_time(void);

/*map*/
void	print_map(const t_map *m);

#endif
