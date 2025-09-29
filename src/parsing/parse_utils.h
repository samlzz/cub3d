/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:21:58 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/28 18:01:06 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include <stdbool.h>
# include <stddef.h>

bool		ft_isspace(int c);
bool		ft_isln_empty(const char *ln);

const char	*ft_skip_sp(const char *p);

bool		ft_is_walkable(char c);
bool		ft_isln_valid(const char *ln, size_t *err_idx);

#endif
