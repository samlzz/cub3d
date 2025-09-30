/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:38:06 by eazard            #+#    #+#             */
/*   Updated: 2025/09/30 16:52:06 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include <X11/Xutil.h>
#include <stdint.h>

#include "cubmap.h"
#include "data/camera.h"
#include "mlx.h"
#include "../data.h"

/* 
 * Handle key press event: update input state in t_inputs
 */
static int	on_key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		data_exit(data, IE_SUCCESS);
	if (keycode == KEY_E)
		data->inputs.try_to_interact_with_door = true;
	else if (keycode == KEY_W)
		data->inputs.forward = true;
	else if (keycode == KEY_S)
		data->inputs.backward = true;
	else if (keycode == KEY_A)
		data->inputs.left = true;
	else if (keycode == KEY_D)
		data->inputs.right = true;
	else if (keycode == XK_Left)
		data->inputs.turn_left = true;
	else if (keycode == XK_Right)
		data->inputs.turn_right = true;
	return (0);
}

/*
 * Handle key release event: reset input state in t_inputs
 */
static int	on_key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->inputs.forward = false;
	else if (keycode == KEY_S)
		data->inputs.backward = false;
	else if (keycode == KEY_A)
		data->inputs.left = false;
	else if (keycode == KEY_D)
		data->inputs.right = false;
	else if (keycode == XK_Left)
		data->inputs.turn_left = false;
	else if (keycode == XK_Right)
		data->inputs.turn_right = false;
	return (0);
}

/*
Handle window close event: clean resources and exit
*/
static int	on_destroy_notify(t_data *data)
{
	data_exit(data, IE_SUCCESS);
	return (0);
}

#ifdef CUB3D_BONUS

int	on_mouse_move(int32_t x, int32_t y, t_data *data)
{
	t_mouse	*cursor;

	cursor = &data->inputs.cursor;
	if (cursor->pending_recenter)
	{
		cursor->pending_recenter = false;
		return (0);
	}
	(void)y;
	cursor->dx_accum += (double)(x - cursor->pos.x);
	cursor->pos = (t_vec2i){WIN_WIDTH / 2, WIN_HEIGHT / 2};
	cursor->pending_recenter = true;
	mlx_mouse_move(data->mlx.display, data->mlx.window,
		cursor->pos.x, cursor->pos.y);
	return (0);
}
#else

int	on_mouse_move(int32_t x, int32_t y, t_data *data);
#endif

/*
Install hooks for key press, key release and window close events
*/
void	install_hooks(t_data *data)
{
	mlx_hook(data->mlx.window, KeyPress, KeyPressMask, &on_key_press, data);
	mlx_hook(data->mlx.window, KeyRelease, KeyReleaseMask,
		&on_key_release, data);
	mlx_hook(data->mlx.window, DestroyNotify, StructureNotifyMask,
		&on_destroy_notify, data);
	if (CUB_BONUS)
		mlx_hook(data->mlx.window, MotionNotify, PointerMotionMask, &on_mouse_move, data);
}
