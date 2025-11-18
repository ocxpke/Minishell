/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:31:11 by pablo             #+#    #+#             */
/*   Updated: 2025/11/17 18:50:26 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minishell.h"

extern volatile sig_atomic_t	g_signal_recv;

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

static char	*heredoc(char *eof)
{
	char	*buffer;
	char	*line;
	char	*trimmed_line;

	buffer = NULL;
	while (1)
	{
		write(STDOUT_FILENO, BOLD "heredoc >" RESET " ", 18);
		line = ft_get_next_line(STDIN_FILENO);
		if (line)
		{
			trimmed_line = ft_strtrim(line, "\n");
			free(line);
			if (!trimmed_line)
				return (ft_get_next_line(-1), ft_free((void **)&buffer),
					perror("Error trimming line"), NULL);
			if (!ft_strncmp(trimmed_line, eof, ft_max_len_str(trimmed_line, eof)) && check_zero_eof(*eof, *trimmed_line))
				return (ft_get_next_line(-1), free(trimmed_line), buffer);
			buffer = process_heredoc_line(buffer, trimmed_line);
			free(trimmed_line);
			if (!buffer)
				return (ft_get_next_line(-1), ft_free((void **)&buffer),
					perror("Error joining heredoc"), NULL);
		}
		else
		{
			if (g_signal_recv == SIGINT)
				return (ft_get_next_line(-1), ft_free((void **)&buffer), NULL);
			// Escalar este problema hasta process_management
			else
				return (ft_get_next_line(-1), write(STDERR_FILENO,
						"Here-document delimited by end-of-file\n", 39),
					buffer);
		}
		// return (ft_free((void **)&buffer), ft_perror("Heredoc error", EINTR,
		// 		0), NULL);
		// Necesidad de si el usuario decide terminar antes con ctrl+d
		// esto ha de seguir, no es error
	}

}

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

int	heredoc_behaviour(char *eof, char **result)
{
	char	*buffer;
	char	*tmp_name;
	int		tmp_file;
	int		save_stdin;

	*result = NULL;
	save_stdin = dup(STDIN_FILENO);
	signal(SIGINT, sigint_heredoc_handler);
	buffer = heredoc(eof);
	if (g_signal_recv == SIGINT)
		dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	signal(SIGINT, sigint_handler);
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
	tmp_file = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_file == -1)
		return (ft_free((void **)&buffer), ft_free((void **)tmp_name),
			perror("Error opening here_doc tmp file"), HEREDOC_ERROR);
	write(tmp_file, buffer, ft_strlen(buffer));
	if (close(tmp_file))
		return (ft_free((void **)&buffer), ft_free((void **)&tmp_name),
			perror("Error closing here_doc tmp file"), HEREDOC_ERROR);
	ft_free((void **)&buffer);
	*result = tmp_name;
	return (HEREDOC_SUCCESS);
}
