/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:46:34 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/29 16:36:16 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

static char	*search_nl(int fd, char *buffer, char **aux_buffer);

/**
 * @brief Allocates a new buffer and frees the old one if it exists.
 *
 * This function allocates a new buffer of size BUFFER_SIZE + 1 and
 * initializes it to zero. If an old buffer is provided, it will be freed
 * before the new buffer is allocated.
 *
 * @param old_buffer A pointer to the old buffer that needs to be freed.
 *                   Can be NULL.
 * @return A pointer to the newly allocated buffer, or NULL if the
 *         allocation fails.
 */
static char	*get_new_buffer(char *old_buffer)
{
	char	*buffer;

	if (old_buffer)
		ft_free((void **)&old_buffer);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	ft_memset(buffer, 0, BUFFER_SIZE + 1);
	return (buffer);
}

/**
 * @brief Processes a line from a file descriptor.
 *
 * This function reads data from the given file descriptor into the provided
 * buffer. It handles the auxiliary buffer to manage the data read across
 * multiple calls. If the read operation indicates the end of the file or an
 * error, it cleans up the buffers and returns the appropriate result.
 *
 * @param fd The file descriptor to read from.
 * @param buffer The buffer to store the read data.
 * @param aux_buffer A pointer to an auxiliary buffer that holds data across
 *                   multiple reads.
 * @return A pointer to the processed line, or NULL if an error occurs or the
 *         end of the file is reached.
 */
static char	*process_line(int fd, char *buffer, char **aux_buffer)
{
	char	*tmp_buffer;
	ssize_t	read_code;

	read_code = read(fd, buffer, BUFFER_SIZE);
	if (read_code < 1)
	{
		ft_free((void **)&buffer);
		if (read_code == 0 && *aux_buffer && **aux_buffer)
		{
			tmp_buffer = ft_strndup(*aux_buffer, 0);
			ft_free((void **)&*aux_buffer);
			*aux_buffer = NULL;
			return (tmp_buffer);
		}
		ft_free((void **)&*aux_buffer);
		*aux_buffer = NULL;
		return (NULL);
	}
	if (*aux_buffer)
	{
		tmp_buffer = buffer;
		buffer = ft_strjoin(*aux_buffer, buffer);
		ft_free((void **)&tmp_buffer);
	}
	return (search_nl(fd, buffer, aux_buffer));
}

/**
 * @brief Keeps searching for a newline character in the file descriptor.
 *
 * This function attempts to find a newline character in the given file
 * descriptor. If the auxiliary buffer is not initialized, it duplicates the
 * current buffer. Otherwise, it frees the previous auxiliary buffer and
 * duplicates the current buffer. Finally, it processes the line by calling
 * `process_line`.
 *
 * @param fd The file descriptor to read from.
 * @param buffer The current buffer containing data read from the file
 *               descriptor.
 * @param aux_buffer A pointer to the auxiliary buffer that stores intermediate
 *                   data.
 * @return A pointer to the processed line.
 **/
static char	*keep_searching_nl(int fd, char *buffer, char **aux_buffer)
{
	char	*tmp_buffer;

	if (!*aux_buffer)
		*aux_buffer = ft_strndup(buffer, 0);
	else
	{
		tmp_buffer = *aux_buffer;
		*aux_buffer = ft_strndup(buffer, 0);
		if (tmp_buffer)
			ft_free((void **)&tmp_buffer);
	}
	return (process_line(fd, get_new_buffer(buffer), aux_buffer));
}

/**
 * @brief Searches for a newline character in the provided buffer.
 *
 * This function searches for a newline character in the provided buffer. If a
 * newline is found, it splits the buffer at the newline, updates the auxiliary
 * buffer with the remaining data, and returns a new buffer containing the data
 * up to and including the newline. If no newline is found, it continues
 * searching by calling the keep_searching_nl function.
 *
 * @param fd The file descriptor to read from.
 * @param buffer The buffer to search for a newline character.
 * @param aux_buffer A pointer to an auxiliary buffer to store the remaining
 *                   data after the newline.
 *
 * @return A new buffer containing the data up to and including the newline if
 *         found, otherwise the result of keep_searching_nl.
 */
static char	*search_nl(int fd, char *buffer, char **aux_buffer)
{
	char	*tmp_buffer;
	size_t	buffer_nl_size;

	if (ft_strchr(buffer, '\n'))
	{
		buffer_nl_size = ft_strchr(buffer, '\n') - buffer + 1;
		if (*aux_buffer)
			ft_free((void **)&*aux_buffer);
		*aux_buffer = ft_strndup(buffer + buffer_nl_size, 0);
		tmp_buffer = ft_strndup(buffer, buffer_nl_size + 1);
		ft_free((void **)&buffer);
		return (tmp_buffer);
	}
	else
	{
		return (keep_searching_nl(fd, buffer, aux_buffer));
	}
}

char	*ft_get_next_line(int fd)
{
	static char	*aux_buffer;
	char		*buffer;
	char		*rtn_buffer;
	size_t		nl_pos;

	if (aux_buffer && ft_strchr(aux_buffer, '\n'))
	{
		nl_pos = ft_strchr(aux_buffer, '\n') - aux_buffer + 1;
		rtn_buffer = ft_strndup(aux_buffer, nl_pos + 1);
		buffer = aux_buffer;
		aux_buffer = ft_strndup(aux_buffer + nl_pos, 0);
		ft_free((void **)&buffer);
		return (rtn_buffer);
	}
	rtn_buffer = process_line(fd, get_new_buffer(NULL), &aux_buffer);
	return (rtn_buffer);
}
