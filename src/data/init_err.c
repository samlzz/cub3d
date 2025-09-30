/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:54:18 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 18:00:58 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>

#include "init_err.h"

const char	*ie_str(t_init_error code)
{
	static const char	*msgs[IE__COUNT] = {
	[IE_SUCCESS] = "success",
	[IE_DESTROY_NOTIFY] = "window closed",
	[IE_MLX_INIT_ERROR] = "failed to initialize MiniLibX",
	[IE_DDA_RAYDIR_VEC_ZERO] = "internal error: DDA ray direction is zero",
	[IE_OPEN_TEXTURE_FAILURE] = "failed to load textures",
	[IE_INSTALLING_DOOR_FAILURE] = "failed to allocate/initialize doors grid",
	};
	int32_t				idx;

	idx = (int32_t)code;
	if (idx < 0 || idx >= (int)IE__COUNT || !msgs[idx])
		return ("unknown initialization error");
	return (msgs[idx]);
}

int32_t	ie_print_err(t_init_error code)
{
	if (code == IE_SUCCESS || code == IE_DESTROY_NOTIFY)
		return (0);
	printf("cub3d: Error: %s\n", ie_str(code));
	return (1);
}
