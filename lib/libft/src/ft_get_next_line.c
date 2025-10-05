/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:12:35 by pablo             #+#    #+#             */
/*   Updated: 2025/10/03 17:12:40 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

/**
 * @brief Appends a memory block to a dynamically allocated string.
 *
 * This function concatenates the contents of `s2` (of length `size2`)
 * to the string pointed to by `*s1`. The result is stored in a newly
 * allocated buffer, which replaces the original `*s1`. The original
 * buffer is freed if it exists.
 *
 * @param s1    Pointer to the string to be appended to. May be NULL.
 *              After the call, `*s1` will point to the new buffer.
 * @param s2    Pointer to the memory block to append.
 * @param size2 Number of bytes from `s2` to append.
 *
 * @return      1 on success, 0 on memory allocation failure.
 */
static int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1;
	char	*tmp;

	size1 = ft_strlen(*s1);
	tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	if (*s1)
	{
		ft_memcpy(tmp, *s1, size1);
		free(*s1);
	}
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	*s1 = tmp;
	return (1);
}

/**
 * @brief Initializes or retrieves the buffer for a file descriptor.
 *
 * If fd is invalid (<0 or >=FD_MAX) and equals -1, all buffers
 * are freed and set to NULL. Otherwise, if the buffer for fd
 * does not exist, it allocates memory for it using ft_calloc.
 *
 * @param fd      The file descriptor to initialize or retrieve.
 * @param buffers Array of buffer pointers, indexed by fd.
 *
 * @return        Pointer to the buffer for fd, or NULL if
 *                allocation fails or fd is invalid.
 */
char	*buffer_init(int fd, char *buffers[])
{
	int	i;

	i = 0;
	if (fd < 0 || fd >= FD_MAX)
	{
		if (fd == -1)
		{
			i = 0;
			while (i < FD_MAX)
			{
				if (buffers[i])
					free(buffers[i]);
				buffers[i] = NULL;
				i++;
			}
		}
		return (NULL);
	}
	if (!buffers[fd])
		buffers[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffers[fd])
		return (NULL);
	return (buffers[fd]);
}

/**
 * @brief Cleans the buffer after extracting a line.
 *
 * Appends the content from buffer `b` up to and including `tmp`
 * to the string pointed to by `ret`. Then, shifts the remaining
 * content in the buffer (after `tmp`) to the beginning of `b`,
 * and null-terminates the buffer.
 *
 * @param ret Pointer to the string to append to.
 * @param b   Buffer containing the data to process.
 * @param tmp Pointer to the position in the buffer up to which
 *            data should be appended.
 * @return    Pointer to the updated string on success, or NULL
 *            on failure.
 */
static char	*clean_buffer(char **ret, char *b, char *tmp)
{
	size_t	len;

	if (!str_append_mem(ret, b, tmp - b + 1))
	{
		free(*ret);
		return (NULL);
	}
	len = ft_strlen(tmp + 1);
	ft_memmove(b, tmp + 1, len);
	b[len] = 0;
	return (*ret);
}

/**
 * @brief Continues reading from a file descriptor until a newline is found or
 *        EOF is reached.
 *
 * This function reads data from the given file descriptor `fd` into buffer `b`
 * and appends it to the string pointed to by `ret`. It uses an array of buffers
 * `buffers[]` to manage per-descriptor storage. The function stops reading when
 * a newline character is encountered in the buffer or when the end of the file
 * is reached. If an error occurs during reading, or if no data is read, it
 * returns NULL. Otherwise, it returns a pointer to the newline character in the
 * buffer.
 *
 * @param fd        The file descriptor to read from.
 * @param buffers   Array of buffers for each file descriptor.
 * @param b         Temporary buffer to store read data.
 * @param ret       Pointer to the string where read data is accumulated.
 * @return          Pointer to the newline character in the buffer if found,
 *                  otherwise NULL on error or end of file.
 */
static char	*keep_reading(int fd, char *buffers[], char *b, char **ret)
{
	char	*tmp;
	int		read_ret;

	tmp = NULL;
	while (!tmp)
	{
		if (!str_append_mem(ret, b, ft_strlen(b)))
			return (NULL);
		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return (NULL);
		if (read_ret == 0)
		{
			free(buffers[fd]);
			buffers[fd] = NULL;
			if (*ret && **ret)
				return (*ret);
			return (NULL);
		}
		b[read_ret] = 0;
		tmp = ft_strchr(b, '\n');
	}
	return (tmp);
}

char	*ft_get_next_line(int fd)
{
	static char	*buffers[FD_MAX];
	char		*b;
	char		*ret;
	char		*tmp;

	b = buffer_init(fd, buffers);
	if (!b)
		return (NULL);
	ret = NULL;
	tmp = ft_strchr(b, '\n');
	if (!tmp)
	{
		tmp = keep_reading(fd, buffers, b, &ret);
		if (!tmp)
			return (NULL);
	}
	return (clean_buffer(&ret, b, tmp));
}
