/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:41:16 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/04 18:24:48 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_LST_H
# define STR_LST_H

#include <stddef.h>

typedef struct s_strlst	t_strlst;
struct s_strlst
{
	char		*str;
	t_strlst	*next;
};

t_strlst	*strlst_new(char *str);
void		strlst_clear(t_strlst *head);

t_strlst	*strlst_getlast(t_strlst *head);
void		strlst_addback(t_strlst **head, t_strlst *new);

#endif
