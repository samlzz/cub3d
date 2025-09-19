/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:46:28 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/19 10:35:51 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xutil.h>
#include <stdio.h>

#include "data/data.h"
#include "libft.h"

/*
 * Debug helper: print key events to stderr (fd 2)
 */
void	print_key_event(int keycode, const char *event)
{
	char	keyname[8];

	ft_bzero(keyname, 8 * sizeof (char));
	if (ft_isalpha(keycode))
		keyname[0] = (char)keycode;
	else if (keycode == XK_Left)
		ft_strlcat(keyname, "left", 5);
	else if (keycode == XK_Right)
		ft_strlcat(keyname, "right", 6);
	else if (keycode == XK_Escape)
		ft_strlcat(keyname, "esc", 4);
	else if (keycode == E_DESTROY_NOTIFY)
		return ((void)fprintf(stderr, "destroy notify event ocured\n"));
	else
		return ((void)(fprintf(stderr, "[event](%s) keycode: %d\n", event, keycode)));
	fprintf(stderr, "[event](%s) key: %s\n", event, keyname);
}
