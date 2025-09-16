/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:09:58 by eazard            #+#    #+#             */
/*   Updated: 2025/09/16 16:37:29 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "vec.h"

void	print_vec2d(t_vec2d vec, char *name)
{
	printf("%s\n", name);
	printf("x = %f\n", vec.x);
	printf("y = %f\n", vec.y);
}

/*
untested
*/
void	print_vec2i(t_vec2i vec, char *name)
{
	printf("%s\n", name);
	printf("x = %i\n", vec.x);
	printf("y = %i\n", vec.y);
}
