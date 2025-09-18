/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:05:42 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/18 10:07:38 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "libft.h"

void	open_err(const char *filename)
{
	char	*str;
	size_t	len;
	int32_t	errno_;

	errno_ = errno;
	len = ft_strlen("cub3d: ") + ft_strlen(filename) + 1;
	str = malloc(len);
	if (!str)
		return (perror("cub3d: malloc"));
	str[0] = 0;
	ft_strlcat(str, "cub3d: ", len);
	ft_strlcat(str, filename, len);
	errno = errno_;
	perror(str);
}
