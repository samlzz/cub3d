/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazard <eazard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:17:58 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/30 15:55:51 by eazard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "color.h"
#include "parsing/parse_utils.h"

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

/* Parse in *out an RGB color like: *RR*,*GG*,*BB* * => n-spaces 
return 0 in case of success
		1 if separators wasn't formated as expected
			(commat surrounded by n-spaces)
		2 if numbers wasn't in expected format (3 unsigned char)
*/
int16_t	parse_rgb_triplet(const char *s, const char **end, t_color *out)
{
	uint8_t		*triplet[3];
	uint8_t		i;

	triplet[0] = &out->code.r;
	triplet[1] = &out->code.g;
	triplet[2] = &out->code.b;
	i = 0;
	while (i < 3)
	{
		s = ft_skip_sp(s);
		if (ft_ato_u8(&s, triplet[i]))
			return (2);
		if (i != 2 && !expect_comma(&s))
			return (1);
		i++;
	}
	if (end)
		*end = ft_skip_sp(s);
	return (0);
}

/* Act as a wrapper of parse_rgb_triplet
check if the string s was completly consumed by it,
	if not return error code 3
*/
int16_t	parse_rgb_line(const char *s, t_color *out)
{
	const char	*end;
	int16_t		code;

	end = NULL;
	code = parse_rgb_triplet(s, &end, out);
	if (code)
		return (code);
	if (end && *end)
		return (3);
	return (0);
}
