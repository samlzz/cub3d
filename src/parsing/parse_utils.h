/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:21:58 by sliziard          #+#    #+#             */
/*   Updated: 2025/09/13 18:03:12 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include <stdbool.h>

bool		ft_isspace(int c);
bool		ft_isln_empty(const char *ln);

const char	*ft_skip_sp(const char *p);

bool		ft_is_walkable(char c);
bool		ft_isln_valid(const char *ln);

#endif
