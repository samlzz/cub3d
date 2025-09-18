/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:41:31 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/18 10:21:19 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm-generic/errno.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "str_lst.h"
#include "libft.h"

t_strlst	*strlst_new(char *str)
{
	t_strlst	*new;
	size_t		tmp;

	new = ft_calloc(1, sizeof (t_strlst));
	if (!new)
		return (perror("cub3d: strlst_new: malloc"), NULL);
	new->str = str;
	if (str)
	{
		tmp = ft_strlen(str);
		if (tmp > INT_MAX)
		{
			errno = EOVERFLOW;
			perror("cub3d: strlstr_new");
			free(new);
			return (NULL);
		}
		new->len = (int32_t)tmp;
	}
	return (new);
}

void	strlst_clear(t_strlst *head)
{
	t_strlst	*next;

	while (head)
	{
		next = head->next;
		free(head->str);
		free(head);
		head = next;
	}
}

t_strlst	*strlst_getlast(t_strlst *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}

void	strlst_addback(t_strlst **head, t_strlst *new)
{
	t_strlst	*last;

	if (!new)
		return ;
	last = strlst_getlast(*head);
	if (last)
		last->next = new;
	else
		*head = new;
}

int16_t	strlst_add_node(t_strlst **head, char *line, int32_t *size)
{
	t_strlst	*new;
	char		*ln;

	if (line)
	{
		ln = ft_strrchr(line, '\n');
		if (ln)
			*ln = '\0';
	}
	new = strlst_new(line);
	if (!new)
		return (1);
	strlst_addback(head, new);
	if (size)
		(*size)++;
	return (0);
}
