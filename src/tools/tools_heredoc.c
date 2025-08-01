/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:31:11 by pablo             #+#    #+#             */
/*   Updated: 2025/08/01 14:25:40 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

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
 * @brief Reads input from stdin until a specified EOF string is encountered.
 *
 * Continuously prompts the user with "heredoc >" and reads lines from stdin.
 * Lines are appended to a buffer until a line matching the EOF string is
 * encountered. The EOF comparison uses `ft_strncmp`. Returns the buffer
 * excluding the EOF line.
 *
 * @param eof The string marking the end of input (EOF).
 * @param eof_size The length of the EOF string.
 * @return A pointer to the buffer with input lines, or NULL on error.
 *
 * @note Memory:
 *
 * - Dynamically allocates memory for the buffer and strings.
 *
 * - Frees memory on errors or successful completion.
 *
 * Errors:
 *
 * - On read or join errors, frees memory, prints an error with `perror`,
 *   and returns NULL.
 */
char	*heredoc(char *eof, size_t eof_size)
{
	char	*buffer;
	char	*line;
	char	*tmp;

	buffer = NULL;
	while (1)
	{
		printf(BOLD "heredoc >" RESET);
		line = ft_get_next_line(STDIN_FILENO);
		if (line)
		{
			if (!ft_strncmp(line, eof, eof_size) && check_zero_eof(*eof, *line))
				return (ft_free((void **)&line), ft_get_next_line(-1), buffer);
			tmp = buffer;
			buffer = ft_strjoin(buffer, line);
			if (tmp)
				ft_free((void **)&tmp);
			ft_free((void **)&line);
			if (!buffer)
				return (ft_free((void **)&buffer), ft_get_next_line(-1),
					perror("Error joining heredoc"), NULL);
		}
		else
			return (ft_free((void **)&buffer), perror("Heredoc error"), NULL);
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

//TODO: Es importante eliminar el archivo temporal al terminar con heredoc
//TODO: Cambiar el nombre de esta funcion a algo que tenga más sentido
char	*set_heredoc_tmp_file(char *eof)
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
