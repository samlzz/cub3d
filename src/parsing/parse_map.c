/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:21:24 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/29 12:31:00 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "str_lst.h"
#include "fields.h"
#include "cubmap.h"
#include "parse_utils.h"
#include "parse_err.h"
#include "parser.h"

static inline t_parse_err	_handle_invalid_map_ln(struct s_diag *d, int32_t i, char c_err)
{
	char	inv_char[4];

	ft_memset(inv_char, '\'', 4);
	inv_char[1] = c_err;
	inv_char[3] = 0;
	d->file_line = i;
	d->what = ft_strjoin(inv_char, " is an invalid map character");
	if (!d->what)
		return (perror("cub3d: parse_grid: malloc"), PE_INTERNAL);
	return (PE_U_MALFORMED);
}

static t_parse_err	_parse_grid(t_strlst *lines, int32_t count, t_grid *grid, struct s_diag *d)
{
	int32_t	i;
	size_t	err_idx;

	grid->dim.y = count;
	grid->grid = ft_calloc(count + 1, sizeof (char *));
	if (!grid->grid)
		return (perror("cub3d: parse_grid: malloc"), PE_INTERNAL);
	grid->dim.x = INT_MIN;
	i = 0;
	while (i < grid->dim.y && lines)
	{
		grid->grid[i] = lines->str;
		if (lines->str)
		{
			if (!ft_isln_valid(lines->str, &err_idx))
				return (_handle_invalid_map_ln(d, i, lines->str[err_idx]));
			if (lines->len > grid->dim.x)
				grid->dim.x = lines->len;
			lines->str = NULL;
		}
		lines = lines->next;
		i++;
	}
	return (PE_OK);
}

t_parse_err	parse_map(t_strlst *content, int32_t size, t_grid *out, struct s_diag *d)
{
	t_parse_err	code;
	t_grid		*n;
	
	code = _parse_grid(content, size, out, d);
	if (code)
		return (code);
	n = get_normalized_grid(out);
	if (!n)
		return (PE_INTERNAL);
	code = validate_map_closed(n);
	free_grid(n);
	free(n);
	return (code);
}
