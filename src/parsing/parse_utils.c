/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:22:45 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/13 18:03:42 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "libft.h"

bool	ft_isspace(int c)
{
	uint8_t	uc;

	uc = (uint8_t)c;
	return (
		uc == ' ' || uc == '\f' \
		|| uc == '\n' || uc == '\r' \
		|| uc == '\t' || uc == '\v'
	);
}

const char *ft_skip_sp(const char *p)
{
	while (ft_isspace(*p))
		p++;
	return (p);
}

bool	ft_isln_empty(const char *ln)
{
	size_t	i;
	size_t	len;
	
	len = ft_strlen(ln);
	i = 0;
	while (ft_isspace(ln[i]))
		i++;
	return (i == len);
}

bool	ft_is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	ft_isln_valid(const char *ln)
{
	size_t	i;

	i = 0;
	while (ln[i]
		&& (ft_is_walkable(ln[i])
			|| ln[i] == ' '
			|| ln[i] == '1'
			|| ln[i] == '\n')
	)
		i++;
	return (ln[i] == '\0');
}