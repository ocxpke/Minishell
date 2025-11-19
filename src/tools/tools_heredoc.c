/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:31:11 by pablo             #+#    #+#             */
/*   Updated: 2025/11/19 17:57:14 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minishell.h"

extern volatile sig_atomic_t	g_signal_recv;

static char	*process_line(char *buffer, char *line, char *eof)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, "\n");
	free(line);
	if (!trimmed_line)
		return (ft_get_next_line(-1), ft_free((void **)&buffer),
			perror("Error trimming line"), NULL);
	if (check_eof_match(trimmed_line, eof))
		return (ft_get_next_line(-1), free(trimmed_line), buffer);
	buffer = process_heredoc_line(buffer, trimmed_line);
	free(trimmed_line);
	if (!buffer)
		return (ft_get_next_line(-1), ft_free((void **)&buffer),
			perror("Error joining heredoc"), NULL);
	return (buffer);
}

static char	*heredoc(char *eof)
{
	char	*buffer;
	char	*line;

	buffer = NULL;
	while (1)
	{
		write(STDOUT_FILENO, BOLD "heredoc >" RESET " ", 18);
		line = ft_get_next_line(STDIN_FILENO);
		if (line)
		{
			buffer = process_line(buffer, line, eof);
			if (!buffer || check_eof_match(buffer, eof))
				return (buffer);
		}
		else
			return (handle_heredoc_eof(buffer));
	}
}

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
