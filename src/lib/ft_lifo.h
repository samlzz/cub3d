/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lifo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:10:43 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/13 19:37:15 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FIFO_H
# define FT_FIFO_H

#include <stddef.h>
# include <stdint.h>

# ifndef FT_FIFO_FACT
#  define FT_FIFO_FACT 2
# endif

typedef struct s_lifo	t_lifo;

struct s_lifo
{
	int32_t	*data;
	size_t	size;
	size_t	cap;
};

int16_t	ft_lifo_init(t_lifo *new, size_t dim);
int16_t	ft_lifo_push(t_lifo *l, int32_t val);
int16_t	ft_lifo_pop(t_lifo *l, int32_t *val);

#endif
