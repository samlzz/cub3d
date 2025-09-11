/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 01:01:59 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/11 14:16:27 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gnl.h"
#include <unistd.h>

/**
 * This function reads data from a file descriptor `fd` and stores it in the
 * `stash` memory structure. It stops when a `*buf_data.content` character is
 * found or when EOF is reached.
 * @return A pointer to the content in the stash, or NULL if an error occurs.
 */
static char	*_get_buff_w_ln(int fd, t_mem *stash, bool *is_EOF, t_mem buf_data)
{
	int		readed;
	char	*buff;
	t_mem	tmp;

	buff = ft_calloc(sizeof (char), buf_data.size);
	if (!buff)
		return (NULL);
	readed = 1;
	while (readed > 0 && !ft_gnl_memchr(stash, *buf_data.content))
	{
		readed = read(fd, buff, buf_data.size);
		if (readed < 0)
			return (free(buff), NULL);
		*is_EOF = (readed == 0);
		if (*is_EOF)
			break ;
		tmp = ft_memjoin(stash, buff, readed);
		if (!tmp.content)
			return (free(buff), NULL);
		free(stash->content);
		*stash = tmp;
	}
	free(buff);
	return (stash->content);
}

/**
 * @brief Extracts a line from the buffer and adjusts the stash.
 * @return The lenght of the extracted line, or -1 if an error occurs.
 */
static ssize_t	_extract_ln_from_buff(t_mem *stash, char **lineptr, int delim)
{
	t_mem			tmp;
	t_mem			line;
	size_t			ln_i;
	unsigned char	*content;

	ln_i = 0;
	content = (unsigned char *)stash->content;
	while (ln_i < stash->size && content[ln_i] != (unsigned char)delim)
		ln_i++;
	line = ft_submem(*stash, 0, ln_i + (ln_i < stash->size));
	if (!line.content)
		return (free_for_quit_gnl(stash));
	tmp = ft_submem(*stash, ln_i + 1, stash->size - ln_i - 1);
	free_for_quit_gnl(stash);
	if (!tmp.content && tmp.size == 1)
		return (free(line.content), -1);
	*stash = tmp;
	*lineptr = line.content;
	(*lineptr)[line.size] = 0;
	return (line.size);
}

__attribute__((destructor))
static void	_ft_getdelim_clean_exit(void)
{
	ft_getdelim(NULL, '0', -1);
}

ssize_t	ft_getdelim(char **lineptr, int delim, int fd)
{
	static t_mem	stash;
	t_mem			data;
	bool			eof_reached;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free_for_quit_gnl(&stash));
	*lineptr = NULL;
	eof_reached = false;
	data.size = BUFFER_SIZE;
	data.content = (char *)(&delim);
	if (!_get_buff_w_ln(fd, &stash, &eof_reached, data))
	{
		return (free_for_quit_gnl(&stash));
	}
	if (eof_reached && (!stash.content || !*stash.content))
	{
		return (free_for_quit_gnl(&stash));
	}
	return (_extract_ln_from_buff(&stash, lineptr, delim));
}

ssize_t	ft_getline(char **lineptr, int fd)
{
	return (ft_getdelim(lineptr, '\n', fd));
}
