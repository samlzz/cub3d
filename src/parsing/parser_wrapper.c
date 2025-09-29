/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 00:10:29 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/28 18:47:25 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>

#include "color.h"
#include "libft.h"
#include "parse_utils.h"
#include "fields.h"
#include "parsing/parse_err.h"

t_parse_err	parse_texture_wrap(const char *after_id, void *tex_path, struct s_diag *d)
{
	char		*tmp;
	const char	*end;
	size_t		len;

	after_id = ft_skip_sp(after_id);
	len = 0;
	while (after_id[len] && !ft_isspace(after_id[len]))
		len++;
	end = ft_skip_sp(after_id + len);
	if (*end)
	{
		d->what = ft_strdup("trailing content after texture path");
		if (!d->what)
			return (perror("cub3d: parse_texture"), PE_INTERNAL);
		return (PE_U_MALFORMED);
	}
	tmp = ft_substr(after_id, 0, len);
	if (!tmp)
		return (perror("cub3d: parse_texture"), PE_INTERNAL);
	*(char **)tex_path = tmp;
	return (PE_OK);
}

t_parse_err	parse_color_wrap(const char *after_id, void *color, struct s_diag *d)
{
	int16_t	code;

	code = parse_rgb_line(after_id, (t_color *)color);
	if (code == 0)
		return (PE_OK);
	if (code == 1)
		return (PE_INTERNAL);
	if (code == 2)
		d->what = ft_strdup("unexpected separator between digits");
	else if (code == 3)
		d->what = ft_strdup("RGB component out of range (0..255)");
	else if (code == 4)
		d->what = ft_strdup("trailing content after color");
	if (!d->what)
		return (perror("cub3d: parse_color"), PE_INTERNAL);
	return (PE_U_MALFORMED);
}
