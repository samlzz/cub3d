/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:17:58 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/05 12:05:36 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "libft.h"
#include "color.h"
#include "parsing/parse_utils.c"

int16_t	ft_ato_u8(const char **ps, uint8_t *out)
{
	const char	*p;
	int32_t		val;
	int32_t		nd;

	p = *ps;
	val = 0;
	nd = 0;
	if (*p < '0' || *p > '9')
		return (1);
	while (*p >= '0' && *p <= '9')
	{
		val = val * 10 + (*p - '0');
		if (val > 255)
			return (1);
		p++;
		nd++;
	}
	if (!nd)
		return (1);
	*ps = p;
	*out = (uint8_t)val;
	return (0);
}

static bool	expect_comma(const char **ps)
{
	const char	*p;

	p = ft_skip_sp(*ps);
	if (*p != ',')
		return (false);
	*ps = p + 1;
	return (true);
}

t_color	*parse_rgb_triplet(const char *s, const char **end)
{
	t_color		*c;
	uint8_t		*triplet[3];
	uint8_t		i;

	c = ft_calloc(1, sizeof (t_color));
	if (!c)
		return (NULL);
	triplet[0] = &c->code.r;
	triplet[1] = &c->code.g;
	triplet[2] = &c->code.b;
	i = 0;
	while (i < 3)
	{
		s = ft_skip_sp(s);
		if (ft_ato_u8(&s, triplet[i]))
			return (free(c), NULL);
		if (i != 2 && !expect_comma(&s))
			return (free(c), NULL);
	}
	if (end)
		*end = ft_skip_sp(s);
	return (c);
}

t_color	*parse_rgb_line(const char *s)
{
	t_color		*new;
	const char	*end;

	new = parse_rgb_triplet(s, &end);
	if (*end)
	{
		free(new);
		new = NULL;
	}
	return (new);
}