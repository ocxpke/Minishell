/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:08:35 by pablo             #+#    #+#             */
/*   Updated: 2025/11/24 20:53:06 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "structs.h"

/**
 * @brief Cleans quotes from the input string by removing unnecessary quote
 * characters.
 *
 * This function processes the string pointed to by *str, removing
 * quotes that are not part of the actual content (e.g., handling
 * escaped or paired quotes). It calculates the size of the cleaned
 * string, processes it if quotes are present, and updates the
 * original string pointer to the cleaned version. If no cleaning is
 * needed or if processing fails, the function returns without
 * modification.
 *
 * @param str A pointer to a pointer to the string to be cleaned. The
 *            string must be null-terminated. If str or *str is NULL,
 *            the function does nothing.
 */
void	clean_quote(char **str);

/**
 * @brief Resolves the command type for the token at index `i`.
 *
 * Checks if the token string is a built-in, a command literal, or needs
 * path resolution.
 * Sets token type to COMMAND_BUILT_IN if built-in.
 * If not built-in and cmd_literal_resolver does not return 2, returns early.
 * Otherwise, tries to resolve the command path.
 * @param tokens Array of token pointers.
 * @param i Index of the token to resolve.
 * @param linked_env Pointer to the linked environment list.
 */
void	cmd_resolver(t_token **tokens, size_t i, t_linked_env *linked_env);

/**
 * @brief Collapses a 3D array of strings into a single 2D array.
 *
 * This function takes a triple pointer to a matrix of strings (`extracted`),
 * calculates the total number of strings contained in all sub-matrices,
 * and returns a new 2D array containing all strings in a single matrix.
 *
 * @param extracted A triple pointer to a 3D array of strings to be collapsed.
 * @return A double pointer to a newly allocated 2D array containing all
 *         strings.
 */
char	**collapse_extracted(char ***extracted);

/**
 * @brief Frees memory allocated for an array of t_token pointers.
 *
 * This function safely iterates through the array of t_token pointers,
 * performing NULL checks before freeing the memory allocated for each
 * token's string and the token itself. Each token pointer is set to NULL
 * after freeing to prevent dangling pointers. Finally, it frees the array of
 * pointers and sets the original pointer to NULL to prevent dangling pointers.
 *
 * @param tokens Pointer to a pointer to an array of t_token pointers to be
 *               freed. After freeing, the pointer is set to NULL.
 */
void	free_tokens(t_token ***tokens);

/**
 * @brief Checks if there is at least one command in the current pipeline.
 *
 * Backtracks from the given index until a pipe or the beginning is reached,
 * checking if any token is classified as a command (COMMAND_BUILT_IN,
 * COMMAND_ROUTE, or COMMAND_NOT_FOUND).
 *
 * @param tokens Array of token pointers.
 * @param i Current token index.
 * @return 1 if a command exists in the pipeline, 0 otherwise.
 */
int		has_command_in_pipeline(t_token **tokens, size_t i);

/**
 * @brief Parses the given command line string into an array of tokens.
 *
 * This function performs the following steps:
 *
 * 1. Checks if the command line is valid and non-empty.
 *
 * 2. Splits the command line by pipes.
 *
 * 3. Splits the resulting strings by quotes.
 *
 * 4. Splits the strings into arguments.
 *
 * 5. Expands environment variables using the provided linked environment.
 *
 * 6. Checks for NULL elements in the processed array; returns NULL if any
 *    are found.
 *
 * 7. Tokenizes the processed strings into an array of tokens.
 *
 * 8. Frees any temporary memory used for splitting.
 *
 *
 * @param command_line The input command line string to parse.
 * @param linked_env   Pointer to the linked list of environment variables
 *                     for expansion.
 * @return             Pointer to an array of token pointers, or NULL if input
 *                     is invalid or if NULL elements are found in the processed
 *                     array.
 */
t_token	**parse(char *command_line, t_linked_env *linked_env);

/**
 * Parses and expands environment variables in a split command line array.
 *
 * This function iterates through each string in the provided array
 * (`splitted`), searching for environment variable references (indicated by
 * '$'). It expands valid environment variables using the provided linked
 * environment list, while skipping those enclosed in quotes. If expansion
 * fails, the entire array is freed and NULL is returned. After processing,
 * quotes are cleaned from each string.
 *
 * @param splitted A null-terminated array of strings representing split
 *                 command line arguments, which may contain environment
 *                 variables to expand.
 * @param linked_env A linked list of environment variables used for
 *                   expansion.
 * @return The modified `splitted` array with expanded environment variables
 *         and cleaned quotes, or NULL if expansion fails.
 */
char	**parse_expand_env(char **splitted, t_linked_env *linked_env);

/**
 * @brief Splits and processes arguments from an array of strings.
 *
 * This function takes an array of strings representing command-line
 * arguments, processes each argument (potentially splitting on spaces,
 * handling quotes, expansions, etc.), and returns a new array of processed
 * arguments. The original array is freed during the process.
 *
 * @param array The input array of strings to be split and processed.
 * @return A new array of strings containing the processed arguments, or
 *         NULL if allocation fails or processing encounters an error.
 */
char	**split_args(char **array);

/**
 * @brief Splits a command line string into an array of strings using the pipe
 *        ('|') character as a delimiter.
 *
 * This function takes an input command line string and splits it into segments
 * wherever a pipe ('|') character is found. Each segment is stored as a
 * separate string in a newly allocated matrix, suitable for further pipe
 * processing.
 *
 * @param command_line The input command line string to be split.
 * @return char** A newly allocated matrix of strings, where each string is a
 *         segment of the command line separated by pipes. Returns NULL if
 *         memory allocation fails.
 *
 * @note The caller is responsible for freeing the returned matrix.
 */
char	**split_pipes(char *command_line);

/**
 * @brief Splits each string in the array by quotes and processes results.
 *
 * Takes an array of strings, splits each by single/double quotes,
 * cleans substrings, and collapses results into a final array.
 * Frees the original array before returning the processed result.
 *
 * @param array Array of strings to split and process. Freed in function.
 * @return Newly allocated array of processed strings, or NULL on failure.
 */
char	**split_quotes(char **array);

/**
 * @brief Tokenizes an array of strings into an array of t_token pointers.
 *
 * This function takes an array of strings, determines its length, and parses
 * it into tokens using first_token_parse. It then classifies each token's
 * arguments using arg_classification.
 *
 * @param array The input array of strings to be tokenized.
 * @param linked_env Pointer to the linked environment list.
 * @return t_token** Pointer to an array of token structures.
 */
t_token	**tokenize(char **array, t_linked_env *linked_env);

#endif
