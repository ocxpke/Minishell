/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_heredoc_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:44:06 by pablo             #+#    #+#             */
/*   Updated: 2025/11/19 18:03:01 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal_recv;

int	check_zero_eof(char eof, char line)
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

char	*process_heredoc_line(char *buffer, char *line)
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

char	*gerate_tmp_heredoc_name(void)
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

int	check_eof_match(char *trimmed_line, char *eof)
{
	if (!ft_strncmp(trimmed_line, eof, ft_max_len_str(trimmed_line, eof))
		&& check_zero_eof(*eof, *trimmed_line))
		return (1);
	return (0);
}

char	*handle_heredoc_eof(char *buffer)
{
	if (g_signal_recv == SIGINT)
		return (ft_get_next_line(-1), ft_free((void **)&buffer), NULL);
	else
		return (ft_get_next_line(-1), write(STDERR_FILENO,
				"Here-document delimited by end-of-file\n", 39), buffer);
}
