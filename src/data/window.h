/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 09:25:30 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 16:56:29 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT	700
# endif
# ifndef WIN_WIDTH
#  define WIN_WIDTH		1100
# endif
# ifndef WIN_NAME
#  define WIN_NAME		"cub3d"
# endif

# ifndef FOV_FACTOR
#  define FOV_FACTOR		0.66
# endif

# ifdef CUB3D_BONUS
#  ifndef MOUSE_SENSITIVITY
#   define MOUSE_SENSITIVITY 0.0025
#  endif
# endif

#endif