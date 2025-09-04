/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 01:02:07 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/04 14:18:30 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gnl.h"
#include <stdint.h>

t_mem	ft_memjoin(t_mem const *m, char const *buffer, int buff_size)
{
	t_mem	dest;
	size_t	total_size;

	dest.size = 0;
	dest.content = NULL;
	if (!buffer)
		return (dest);
	total_size = m->size + buff_size;
	dest.content = ft_calloc(total_size, sizeof (char));
	if (!dest.content)
		return (dest);
	if (m->content && m->size > 0)
		ft_memmove(dest.content, m->content, m->size);
	ft_memmove(dest.content + m->size, buffer, buff_size);
	dest.size = total_size;
	return (dest);
}

t_mem	ft_submem(t_mem const m, unsigned int start, size_t len)
{
	t_mem	dest;
	size_t	i;

	dest.content = NULL;
	dest.size = 0;
	if (start >= m.size || len == 0)
		return (dest);
	if (start + len > m.size)
		len = m.size - start;
	dest.content = ft_calloc(sizeof (char), len + 1);
	if (!dest.content)
	{
		dest.size = 1;
		return (dest);
	}
	i = 0;
	while (i < len)
	{
		dest.content[i] = m.content[start + i];
		i++;
	}
	dest.size = len;
	return (dest);
}

char	*ft_gnl_memchr(t_mem const *m, int c)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	*s;

	i = 0;
	uc = (unsigned char)c;
	s = (unsigned char *)m->content;
	while (i < m->size)
	{
		if (*s == uc)
			return ((char *)s);
		i++;
		s++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (ft_getdelim(&line, '\n', fd) < 0)
	{
		return (NULL);
	}
	return (line);
}
