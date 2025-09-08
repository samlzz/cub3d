/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   install_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:38:06 by eazard            #+#    #+#             */
/*   Updated: 2025/09/08 16:10:06 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

/* 
 * Handle key press event: update input state in t_inputs
 */
static int	on_key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		clear_data(data, true, DESTROY_NOTIFY);
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
	clear_data(data, true, 0);
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
