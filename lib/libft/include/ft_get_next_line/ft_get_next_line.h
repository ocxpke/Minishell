/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:46:34 by pabmart2          #+#    #+#             */
/*   Updated: 2025/10/03 17:11:44 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# define FD_MAX 1024

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

/**
 * @brief Reads a line from a file descriptor.
 *
 * This function reads from the given file descriptor `fd` and returns a
 * dynamically allocated string containing the next line, including the newline
 * character if present. It uses a static buffer for each file descriptor to
 * handle partial reads and maintain state between calls.
 *
 * If `fd` is -1, all buffers are freed and set to NULL.
 *
 * @param fd The file descriptor to read from.
 * @return A pointer to the next line read from the file descriptor, or NULL if
 *         there is nothing left to read or an error occurs.
 */
char	*ft_get_next_line(int fd);

#endif
