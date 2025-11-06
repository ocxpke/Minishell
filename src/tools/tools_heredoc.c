/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:31:11 by pablo             #+#    #+#             */
/*   Updated: 2025/11/06 20:18:38 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minishell.h"

/**
 * @brief Checks if the EOF char is zero and line char is a newline.
 *
 * Used to determine if heredoc input reached a special EOF condition.
 * If 'eof' is '\0' and 'line' is '\n', returns 1 (true). If 'eof' is
 * '\0' but 'line' is not '\n', returns 0 (false). In all other cases,
 * returns 1.
 *
 * @param eof  The EOF character to check.
 * @param line The current line character to check.
 * @return int 1 if the EOF condition is met, otherwise 0.
 */
static int	check_zero_eof(char eof, char line)
{
	if (eof == '\0')
	{
		if (line == '\n')
			return (1);
		else
			return (0);
	}
	return (1);
}

/**
 * @brief Appends a line and newline to the heredoc buffer.
 *
 * Concatenates the given line to the buffer, then appends a newline.
 * Handles memory freeing for temporary buffers.
 *
 * @param buffer Current heredoc buffer (may be NULL or allocated).
 * @param line   Line to append (should not be NULL).
 * @return Newly allocated buffer with the line and newline appended,
 *         or NULL on allocation failure. Caller must free the result.
 */
static char	*process_heredoc_line(char *buffer, char *line)
{
	char	*tmp;
	char	*new_buffer;

	tmp = buffer;
	new_buffer = ft_strjoin(buffer, line);
	if (!new_buffer)
		return (ft_free((void **)&tmp), NULL);
	ft_free((void **)&tmp);
	tmp = new_buffer;
	buffer = ft_strjoin(tmp, "\n");
	ft_free((void **)&tmp);
	return (buffer);
}

/**
 * @brief Reads lines from stdin until a specified EOF marker is found,
 *        accumulating the input into a buffer.
 *
 * Prompts the user with "heredoc > " and reads lines using readline().
 * Each line is appended to a buffer unless it matches the EOF marker
 * (eof) with the given size (eof_size) and passes check_zero_eof().
 * If the EOF marker is detected, the buffer is returned.
 * Handles memory allocation and input errors, freeing resources and
 * printing error messages.
 *
 * @param eof      The string that marks the end of heredoc input.
 * @param eof_size The length of the EOF marker to compare.
 * @return         Pointer to the buffer with heredoc input, or NULL on
 *                 error or interruption.
 */
static char	*heredoc(char *eof, size_t eof_size)
{
	char	*buffer;
	char	*line;

	buffer = NULL;
	while (1)
	{
		line = readline(BOLD "heredoc > " RESET);
		if (line)
		{
			if (!ft_strncmp(line, eof, eof_size) && check_zero_eof(*eof, *line))
				return (free(line), buffer);
			buffer = process_heredoc_line(buffer, line);
			free(line);
			if (!buffer)
				return (ft_free((void **)&buffer),
					perror("Error joining heredoc"), NULL);
		}
		else
			return (ft_free((void **)&buffer), ft_perror("Heredoc error", EINTR,
					0), NULL);
	}
}

/**
 * @brief Generates a unique temporary filename for heredoc usage.
 *
 * This function creates a filename in the format ".heredoc_tmpN", where N is an
 * integer starting from 0 and incremented until a writable file with that name
 * does not already exist. It ensures that the generated filename does not
 * collide with any existing writable file in the current directory.
 *
 * @return
 *   A pointer to the newly allocated string containing the unique filename,
 *   or NULL if memory allocation fails at any point.
 *
 * @note
 *   The returned string must be freed by the caller.
 */
static char	*gerate_tmp_heredoc_name(void)
{
	int		n;
	char	*tmp_name;
	char	*tmp_n;

	n = 0;
	tmp_n = ft_itoa(n);
	tmp_name = ft_strjoin(".heredoc_tmp", tmp_n);
	if (!tmp_n || !tmp_name)
		return (NULL);
	while (access(tmp_name, W_OK) != -1)
	{
		ft_free((void **)&tmp_n);
		ft_free((void **)&tmp_name);
		tmp_n = ft_itoa(++n);
		tmp_name = ft_strjoin(".heredoc_tmp", tmp_n);
		if (!tmp_n || !tmp_name)
			return (NULL);
	}
	errno = 0;
	ft_free((void **)&tmp_n);
	return (tmp_name);
}

char	*heredoc_behaviour(char *eof)
{
	char	*buffer;
	char	*tmp_name;
	int		tmp_file;

	buffer = heredoc(eof, ft_strlen(eof));
	if (!buffer)
		return (NULL);
	tmp_name = gerate_tmp_heredoc_name();
	if (!tmp_name)
		return (ft_free((void **)&buffer),
			perror("Error generating heredoc tmp filename"), NULL);
	tmp_file = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_file == -1)
		return (ft_free((void **)&buffer), ft_free((void **)tmp_name),
			perror("Error opening here_doc tmp file"), NULL);
	write(tmp_file, buffer, ft_strlen(buffer));
	if (close(tmp_file))
		return (ft_free((void **)&buffer), ft_free((void **)&tmp_name),
			perror("Error closing here_doc tmp file"), NULL);
	ft_free((void **)&buffer);
	return (tmp_name);
}
