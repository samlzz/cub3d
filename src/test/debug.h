/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:41:55 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/19 11:13:31 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "test.h"

# ifdef DEBUG_MODE

# define PARSING_ONLY					0
# define PARSING_PRINT_GRID				1
# define PARSING_PRINT_NORMALIZED_GRID	0

# define LOOP_PRINT_KEY_EVENT			1
# define LOOP_PRINT_MOUSE_POS			1
# define LOOP_PRINT_CAM_VECS_BEFORE_UPD	0
# define LOOP_PRINT_CAM_VECS_AFTER_UPD	0
# define LOOP_PRINT_DELTA_FRAME			0

# define UNTEXTURED_RAYCASTING_DEBUG	0

# else

# define PARSING_ONLY					0
# define PARSING_PRINT_GRID				1
# define PARSING_PRINT_NORMALIZED_GRID	0

# define LOOP_PRINT_KEY_EVENT			0
# define LOOP_PRINT_MOUSE_POS			0
# define LOOP_PRINT_CAM_VECS_BEFORE_UPD	0
# define LOOP_PRINT_CAM_VECS_AFTER_UPD	0
# define LOOP_PRINT_DELTA_FRAME			0

# define UNTEXTURED_RAYCASTING_DEBUG	0

# endif

#endif
