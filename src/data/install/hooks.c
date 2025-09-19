/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:38:06 by eazard            #+#    #+#             */
/*   Updated: 2025/09/19 10:54:38 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>

#include "mlx.h"
#include "../data.h"
#include "test/debug.h"

/* 
 * Handle key press event: update input state in t_inputs
 */
static int	on_key_press(int keycode, t_data *data)
{
	if (LOOP_PRINT_KEY_EVENT)
		print_key_event(keycode, "onKeyPress");
	if (keycode == KEY_ESC)
		clear_data(data, true, EC_SUCCESS);
	if (keycode == KEY_W)
		data->inputs.forward = true;
	else if (keycode == KEY_S)
		data->inputs.backward = true;
	else if (keycode == KEY_A)
		data->inputs.left = true;
	else if (keycode == KEY_D)
		data->inputs.right = true;
	else if (keycode == KEY_LEFT)
		data->inputs.turn_left = true;
	else if (keycode == KEY_RIGHT)
		data->inputs.turn_right = true;
	return (0);
}

/*
 * Handle key release event: reset input state in t_inputs
 */
static int	on_key_release(int keycode, t_data *data)
{
	if (LOOP_PRINT_KEY_EVENT)
		print_key_event(keycode, "onKeyRelease");
	if (keycode == KEY_W)
		data->inputs.forward = false;
	else if (keycode == KEY_S)
		data->inputs.backward = false;
	else if (keycode == KEY_A)
		data->inputs.left = false;
	else if (keycode == KEY_D)
		data->inputs.right = false;
	else if (keycode == KEY_LEFT)
		data->inputs.turn_left = false;
	else if (keycode == KEY_RIGHT)
		data->inputs.turn_right = false;
	return (0);
}

/*
Handle window close event: clean resources and exit
*/
static int	on_destroy_notify(t_data *data)
{
	clear_data(data, true, EC_SUCCESS);
	return (0);
}

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
}
