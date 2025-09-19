/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:50:47 by eazard            #+#    #+#             */
/*   Updated: 2025/09/19 10:51:43 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

// *Forward declaration

typedef struct s_camera	t_camera;
typedef struct s_map	t_map;
typedef struct s_grid	t_grid;
typedef struct s_vec2d	t_vec2d;
typedef struct s_vec2i	t_vec2i;

// *Print Functions

/*map*/
void	print_grid(const t_grid *g);
void	print_map(const t_map *m);

/*events*/
void	print_key_event(int keycode, const char *event);

/*vec*/

void	vec2d_print(t_vec2d vec, char *name);
void	vec2i_print(t_vec2i vec, char *name);

void	camera_print(t_camera camera);

#endif
