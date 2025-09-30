/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:05:42 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 15:54:24 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "parsing/fields.h"
#include "parsing/parser.h"
#include "parse_err.h"

const char	*pe_str(t_parse_err code)
{
	static const char	*_pe_msgs[PE__COUNT] = {
		"ok",
		"internal error",
		"duplicate key",
		"malformed value",
		"unknown key",
		"missing required field",
		"missing map",
		"missing player on map",
		"too many players on map",
		"map must be surrounded by walls",
		"map must contains at least one walkable tile",
		"unexpected trailing content"
	};
	int32_t				idx;

	idx = (int32_t)code;
	if (idx < 0 || idx >= PE__COUNT)
		return ("error out of bounds");
	return (_pe_msgs[idx]);
}

void	pe_print_err(const struct s_diag *d,
	const t_field *specs, t_parse_err code)
{
	if (d->filename)
	{
		if (d->file_line > 0)
			printf("%s:%d: ", d->filename, d->file_line + 1);
		else
			printf("%s: ", d->filename);
	}
	printf("Error: %s", pe_str(code));
	if (d->owner >= 0 && d->owner < FI__COUNT)
		printf(" (key '%s')", specs[d->owner].metadata.key);
	if (d->what)
		printf("  -> %s\n", d->what);
	else
		printf("\n");
}

void	pe_diag_reset(struct s_diag *d)
{
	if (!d)
		return ;
	free(d->what);
	d->what = NULL;
	d->owner = FI_INVALID;
}

void	pe_quit(t_parser *p, t_parse_err code)
{
	if (!p)
		return ;
	pe_print_err(&p->diag, p->specs, code);
	pe_diag_reset(&p->diag);
}

void	open_err(const char *filename)
{
	char	*str;
	size_t	len;
	int32_t	errno_;

	errno_ = errno;
	len = ft_strlen("cub3d: ") + ft_strlen(filename) + 1;
	str = malloc(len);
	if (!str)
		return (perror("cub3d: malloc"));
	str[0] = 0;
	ft_strlcat(str, "cub3d: ", len);
	ft_strlcat(str, filename, len);
	errno = errno_;
	perror(str);
	free(str);
}
