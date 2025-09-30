/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_err.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:54:31 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 18:03:07 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_ERR_H
# define INIT_ERR_H

# include <stdint.h>

typedef enum e_init_error	t_init_error;

enum e_init_error
{
	IE_SUCCESS,
	IE_DESTROY_NOTIFY,
	IE_MLX_INIT_ERROR,
	IE_DDA_RAYDIR_VEC_ZERO,
	IE_OPEN_TEXTURE_FAILURE,
	IE_INSTALLING_DOOR_FAILURE,
	IE__COUNT
};

const char	*ie_str(t_init_error code);
int32_t		ie_print_err(t_init_error code);

#endif
