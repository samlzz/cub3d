/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 01:01:52 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/11 14:19:21 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GNL_H
# define FT_GNL_H

# include <stdlib.h>

// *UTILS

# ifndef LIBFT_H

#  include <stddef.h>
#  include <stdbool.h>

# else

#  include "private/libft_internal.h"

# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

//* Main functions

ssize_t	ft_getdelim(char **lineptr, int delim, int fd);
ssize_t	ft_getline(char **lineptr, int fd);
char	*get_next_line(int fd);

# ifndef LIBFT_H
// *in libft

typedef struct s_mem
{
	char	*content;
	size_t	size;
}	t_mem;

void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t n);
# endif

// *GNL utils:

ssize_t	free_for_quit_gnl(t_mem *stash);

/**
 * @brief Joins two memory segments into a single memory block.
 *
 * Combines the content of a memory structure `m` and a buffer `buffer` into a 
 * new memory block.
 *
 * @param m The memory structure containing the first data segment.
 * @param buffer The buffer containing the second data segment.
 * @param buff_size The size of the buffer.
 * @return A new memory structure containing the combined data, or 
 * an empty structure on failure.
 * @see ft_strjoin
 */
t_mem	ft_memjoin(t_mem const *mem, char const *buffer, int buff_size);

/**
 * @brief Extracts a submemory block from a memory structure.
 *
 * Copies a subset of memory from `m`, starting at `start` and copying up 
 * to `len` bytes.
 *
 * @param m The original memory structure.
 * @param start The starting index of the submemory.
 * @param len The number of bytes to copy.
 * @return A new memory structure containing the subset of memory, or 
 * an empty structure on failure.
 * @see ft_substr
 */
t_mem	ft_submem(t_mem const m, unsigned int start, size_t len);

/**
 * @brief Searches for a character in a memory structure.
 *
 * Looks for the first occurrence of the character `c` in 
 * the memory structure `m`.
 *
 * @param m The memory structure to search.
 * @param c The character to find.
 * @return A pointer to the first occurrence of the character, or 
 * NULL if not found.
 * @see ft_memchr
 */
char	*ft_gnl_memchr(t_mem const *m, int c);

#endif
