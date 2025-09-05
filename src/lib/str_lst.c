/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:41:31 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/04 18:25:09 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>

#include "str_lst.h"
#include "libft.h"

t_strlst	*strlst_new(char *str)
{
	t_strlst	*new;

	new = ft_calloc(sizeof (t_strlst), 1);
	if (!new)
		return (NULL);
	new->str = str;
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
