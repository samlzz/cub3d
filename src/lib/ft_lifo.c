/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lifo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:10:54 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/14 18:08:41 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

#include "ft_lifo.h"
#include "ft_gnl.h"
#include "libft.h"

int16_t	ft_lifo_init(t_lifo *new, size_t dim)
{
	new->cap = dim;
	new->data = ft_calloc(dim, sizeof(int32_t));
	if (!new->data)
		return (1);
	new->size = 0;
	return (0);
}

int16_t	ft_lifo_push(t_lifo *l, int32_t val)
{
	int8_t	*tmp;

	if (l->size >= l->cap)
	{
		l->cap *= FT_FIFO_FACT;
		tmp = ft_realloc(l->data, l->size, l->cap);
		if (!tmp)
			return (1);
	}
	l->data[l->size++] = val;
	return (0);
}

int16_t	ft_lifo_pop(t_lifo *l, int32_t *val)
{
	int32_t	popped;

	if (!l->size)
		return (1);
	if (!val)
		return (2);
	popped = l->data[l->size];
	l->size--;
	*val = popped;
	return (0);
}
