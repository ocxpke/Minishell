/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:46:34 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/29 14:18:42 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

/**
 * @brief Reads a line from a file descriptor.
 *
 * This function reads a line from the given file descriptor and returns it
 * as a dynamically allocated string. It uses a static buffer to store
 * leftover data between calls. If a newline character is found in the
 * static buffer, it returns the line up to and including the newline.
 * Otherwise, it reads more data from the file descriptor until a newline
 * is found or the end of the file is reached.
 *
 * @param fd: The file descriptor to read from.
 *
 * @return A pointer to the line read from the file descriptor, or NULL if
 *         there is no more data to read or an error occurs.
 */
char	*ft_get_next_line(int fd);

/**
 * Sets the first n bytes of the memory area pointed to by s to the specified
 * value.
 *
 * @param s Pointer to the memory area to be filled.
 * @param c Value to be set. The value is passed as an int, but the function
 *          fills the memory area using the unsigned char conversion of this
 *          value.
 * @param n Number of bytes to be set to the value.
 * @return Pointer to the memory area s.
 */
void	*ft_memset(void *s, int c, size_t n);

/**
 * @brief Duplicates a string.
 *
 * This function allocates sufficient memory for a copy of the n characters from
 * the string s, or until a '\0' character if n = 0. It does the copy,
 * and returns a pointer to it. The memory allocated for the new string is
 * obtained with malloc, and can be freed with free.
 *
 * @param s The string to duplicate.
 * @param n The numbers of characters to copy if n > 0
 * @return A pointer to the duplicated string, or NULL if insufficient memory
 *         was available.
 */
char	*ft_strndup(const char *s, size_t n);

/**
 * Appends the string pointed by `src` to the end of the string pointed to
 * by `dst`. It will append at most `size - strlen(dst) - 1` characters,
 * null-terminating the result.
 *
 * @param dst The destination string.
 * @param src The source string.
 * @param size The size of the destination buffer.
 * @return The total length of the string that would have been created if
 *         `size` was large enough. If the return value is greater than or
 *         equal to `size`, truncation occurred.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/**
 * @brief Searches for the first occurrence of a character in a string.
 *
 * This function searches for the first occurrence of the character 'c' in the
 * string 's'. If the character is found, a pointer to the first occurrence is
 * returned. If the character is not found and 'c' is the null terminator, a
 * pointer to the null terminator of 's' is returned. If the character is not
 * found, NULL is returned.
 *
 * @param s The string to be searched.
 * @param c The character to be found.
 * @return A pointer to the first occurrence of 'c' in 's', or NULL if 'c' is
 *         not found.
 */
char	*ft_strchr(const char *s, int c);

/**
 * @brief Concatenates two strings into a new string.
 *
 * This function takes two null-terminated strings, `s1` and `s2`, and
 * concatenates them into a newly allocated string. The new string is
 * dynamically allocated and must be freed by the caller.
 *
 * @param s1 The first string to concatenate.
 * @param s2 The second string to concatenate.
 * @return A pointer to the newly allocated string containing the
 * concatenated result of `s1` and `s2`, or NULL if memory allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2);
#endif
