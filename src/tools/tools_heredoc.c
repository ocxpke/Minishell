/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:31:11 by pablo             #+#    #+#             */
/*   Updated: 2025/11/20 17:51:09 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minishell.h"

extern volatile sig_atomic_t	g_signal_recv;

/**
 * Processes a single line read from input during heredoc expansion.
 *
 * This function trims the newline character from the input line,
 * checks if it matches the end-of-file (EOF) delimiter, and if not,
 * appends the processed line to the buffer. It handles memory
 * management for the line and buffer, returning appropriate status
 * codes.
 *
 * @param buffer A pointer to a string buffer where the heredoc
 *               content is accumulated. The buffer is modified in
 *               place and may be freed on error.
 * @param line   The raw line read from input, which will be freed
 *               by this function.
 * @param eof    The EOF delimiter string to check against the
 *               trimmed line.
 * @return       0 on success (line appended to buffer),
 *               1 if the line matches the EOF delimiter (indicating
 *               end of heredoc),
 *               -1 on error (e.g., memory allocation failure).
 */
static int	process_line(char **buffer, char *line, char *eof)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, "\n");
	free(line);
	if (!trimmed_line)
		return (ft_free((void **)buffer), perror("Error trimming line"), -1);
	if (check_eof_match(trimmed_line, eof))
		return (free(trimmed_line), 1);
	*buffer = process_heredoc_line(*buffer, trimmed_line);
	free(trimmed_line);
	if (!*buffer)
		return (ft_free((void **)buffer), perror("Error joining heredoc"), -1);
	return (0);
}

/**
 * @brief Reads input from stdin until a specified end-of-file marker
 * is encountered.
 *
 * This function implements a heredoc mechanism, prompting the user
 * with "heredoc >" and reading lines from standard input. It
 * accumulates the input into a buffer until the end-of-file marker
 * (eof) is matched. If the eof is found, the buffer is returned. If
 * an error occurs during processing, NULL is returned. If EOF is
 * reached without finding eof, it handles the case accordingly.
 *
 * @param eof The end-of-file marker string to stop reading input.
 * @return A pointer to the accumulated buffer string, or NULL on
 * error or if eof is not found.
 */
static char	*heredoc(char *eof)
{
	char	*buffer;
	char	*line;
	int		result;

	buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	while (1)
	{
		write(STDOUT_FILENO, BOLD "heredoc >" RESET " ", 18);
		line = ft_get_next_line(STDIN_FILENO);
		if (line)
		{
			result = process_line(&buffer, line, eof);
			if (result == 1)
				return (buffer);
			else if (result == -1)
				return (NULL);
		}
		else
			return (handle_heredoc_eof(buffer));
	}
}

/**
 * @brief Sets up signal handling for heredoc input and reads input until
 * the end-of-file delimiter.
 *
 * This function duplicates the standard input file descriptor,
 * installs a custom SIGINT handler for heredoc operations, reads
 * input from the user until the specified EOF delimiter is
 * encountered, and restores the original stdin and signal handler.
 * If a SIGINT signal is received during input, it restores stdin
 * from the saved duplicate.
 *
 * @param eof A null-terminated string representing the end-of-file
 * delimiter for heredoc input.
 * @param save_stdin A pointer to an integer where the duplicated
 * stdin file descriptor will be stored. This is used to restore
 * stdin if interrupted.
 * @return A pointer to a dynamically allocated string containing
 * the heredoc input, or NULL on failure. The caller is responsible
 * for freeing the returned buffer.
 */
static char	*setup_heredoc_signals(char *eof, int *save_stdin)
{
	char	*buffer;

	*save_stdin = dup(STDIN_FILENO);
	signal(SIGINT, sigint_heredoc_handler);
	buffer = heredoc(eof);
	if (g_signal_recv == SIGINT)
		dup2(*save_stdin, STDIN_FILENO);
	close(*save_stdin);
	signal(SIGINT, sigint_handler);
	return (buffer);
}

/**
 * @brief Writes the heredoc buffer content to a temporary file.
 *
 * This function creates or truncates a temporary file with the
 * specified name, writes the provided buffer content to it, and
 * closes the file. If any operation fails, it frees the buffer
 * and tmp_name, prints an error message, and returns an error
 * code.
 *
 * @param buffer The null-terminated string buffer containing the
 * heredoc content to write.
 * @param tmp_name The name of the temporary file to create or
 * overwrite.
 * @return HEREDOC_SUCCESS on success, HEREDOC_ERROR on failure.
 */
static int	write_heredoc_to_file(char *buffer, char *tmp_name)
{
	int	tmp_file;

	tmp_file = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_file == -1)
		return (ft_free((void **)&buffer), ft_free((void **)&tmp_name),
			perror("Error opening here_doc tmp file"), HEREDOC_ERROR);
	write(tmp_file, buffer, ft_strlen(buffer));
	if (close(tmp_file))
		return (ft_free((void **)&buffer), ft_free((void **)&tmp_name),
			perror("Error closing here_doc tmp file"), HEREDOC_ERROR);
	return (HEREDOC_SUCCESS);
}

int	heredoc_behaviour(char *eof, char **result)
{
	char	*buffer;
	char	*tmp_name;
	int		save_stdin;
	int		status;

	*result = NULL;
	buffer = setup_heredoc_signals(eof, &save_stdin);
	if (!buffer)
	{
		if (g_signal_recv == SIGINT)
			return (HEREDOC_INTERRUPTED);
		return (HEREDOC_ERROR);
	}
	tmp_name = gerate_tmp_heredoc_name();
	if (!tmp_name)
		return (ft_free((void **)&buffer),
			perror("Error generating heredoc tmp filename"), HEREDOC_ERROR);
	status = write_heredoc_to_file(buffer, tmp_name);
	if (status != HEREDOC_SUCCESS)
		return (status);
	ft_free((void **)&buffer);
	*result = tmp_name;
	return (HEREDOC_SUCCESS);
}
