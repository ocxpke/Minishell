/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:17:00 by pabmart2          #+#    #+#             */
/*   Updated: 2025/07/30 19:53:43 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

/**
 * float.h has a bug in the norminette because it is the name of a type
 * and the norminette interprets it differently:
 * https://github.com/42School/norminette/issues/470
 */

# include <errno.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "ft_get_next_line/ft_get_next_line.h"
# include "ft_printf/ft_printf.h"


/**
 * @brief A structure representing a node in a linked list.
 *
 * This structure is used to create a linked list where each node contains
 * a pointer to some content and a pointer to the next node in the list.
 *
 * @param content
 * A pointer to the content stored in the node.
 *
 * @param next
 * A pointer to the next node in the linked list.
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/**
 * @brief Converts a string to an integer.
 *
 * This function takes a string `nptr` and converts it to an integer. It skips
 * any leading whitespace characters and then checks for an optional sign
 * character ('-' or '+'). If a '-' sign is found, the resulting integer will
 * be negative. After that, it iterates through the string and converts each
 * digit character to its corresponding integer value. The function stops
 * converting when it encounters a non-digit character. The final result is
 * multiplied by the sign value and returned.
 *
 * @param nptr The string to be converted to an integer.
 * @return The converted integer value.
 */
int					ft_atoi(const char *nptr);

/**
 * @brief Converts a string to a long integer.
 *
 * This function parses the input string `nptr` and converts it to a long
 * integer. It handles optional leading whitespace, an optional '+' or '-'
 * sign, and numeric characters. If the input string contains non-numeric
 * characters after the numeric portion, they are ignored.
 *
 * @param nptr A pointer to the null-terminated string to be converted.
 *             The string may begin with whitespace and an optional sign.
 * @return The converted long integer value. If the string represents a
 *         negative number, the result will be negative.
 *
 * @note This function assumes that the input string is well-formed and does
 *       not handle overflow or invalid input errors.
 */
long				ft_atol(const char *nptr);

/**
 * Sets the first n bytes of the memory pointed to by s to zero.
 *
 * @param s Pointer to the memory to be zeroed.
 * @param n Number of bytes to be zeroed.
 */
void				ft_bzero(void *s, size_t n);

/**
 * @brief Allocates memory for an array of elements and initializes them to 0.
 *
 * This function allocates memory for an array of `nmemb` elements,
 * each of `size` bytes, and initializes all the allocated memory to 0.
 * The total size of the allocated memory is calculated as `nmemb * size`.
 *
 * @param nmemb The number of elements to allocate memory for.
 * @param size The size of each element in bytes.
 * @return On success, a pointer to the allocated memory is returned.
 *         If either `nmemb` or `size` is 0, or if the multiplication of
 *         `nmemb` and `size` exceeds `INT_MAX`, then`NULL` is returned.
 *
 * @note If memory allocation fails, errno is set to ENOMEM.
 */
void				*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief Frees the memory pointed to by the given pointer and sets it to NULL.
 *
 * This function takes a double pointer to a memory location, frees the memory
 * it points to, and then sets the pointer to NULL to avoid dangling pointers,
 *
 * If the pointer is NULL, it does nothing.
 *
 * @param ptr A double pointer to the memory to be freed. The pointer itself
 *            must not be NULL, but the memory it points to can be NULL.
 *
 * @note It is the caller's responsibility to ensure that the pointer passed
 *       to this function was allocated dynamically (e.g., using malloc, calloc,
 *       or realloc).
 */
void				ft_free(void **ptr);

/**
 * @brief Frees a pointer, prints an error message, and optionally exits.
 *
 * Frees a dynamically allocated pointer, prints an error message, and
 * optionally terminates the program.
 *
 * @param msg Error message to be printed.
 * @param err Error code for the message.
 * @param exit Non-zero to terminate the program.
 * @param ptr Double pointer to the memory to free.
 */
void				ft_errfree(char *msg, char err, char exit, void **ptr);

/**
 * @brief Splits a string into an array of substrings based on delimiters.
 *
 * This function takes a string `s` and splits it into fragments separated
 * by any of the delimiter characters in `separators`. It returns a NULL-
 * terminated array of strings, where each element is a substring extracted
 * from `s`. Memory for the array and the substrings is dynamically
 * allocated.
 *
 * @param s The input string to be split.
 * @param separators The string containing delimiter characters used to
 * split the string.
 * @return A NULL-terminated array of substrings on success, or NULL on
 * failure (e.g., if memory allocation fails or if `s` is NULL).
 *
 * @note The caller is responsible for freeing the returned array and its
 * contents.
 */
char				**ft_extractm(char const *s, char const *separators);

/**
 * @brief Retrieves the value of an environment variable.
 *
 * This function searches the environment list for a string that matches the
 * environment variable name provided in `env_var`. If a match is found, the
 * function returns a pointer to the value of the environment variable.
 *
 * @param env_var The name of the environment variable to search for.
 * @return A pointer to the value of the environment variable if found,
 *         otherwise NULL.
 */
char				*ft_getenv(const char *env_var);

/**
 * Checks if the given character is alphanumeric.
 *
 * @param c The character to be checked.
 * @return 1 if the character is alphanumeric, 0 otherwise.
 * @see ft_isalpha
 * @see ft_isdigit
 */
int					ft_isalnum(int c);

/**
 * Checks if the given character is alphabetic.
 *
 * @param c The character to be checked.
 * @return 1 if the character is alphabetic, 0 otherwise.
 */
int					ft_isalpha(int c);

/**
 * Checks if the given character is inside the default ASCII table.
 *
 * @param c The character to be checked.
 * @return 1 if the character is ASCII, 0 otherwise.
 */
int					ft_isascii(int c);

/**
 * Checks if the given character is numeric.
 *
 * @param c The character to be checked.
 * @return 1 if the character is numeric, 0 otherwise.
 */
int					ft_isdigit(int c);

/**
 * Checks if the given character is printable
 *
 * @param c The character to be checked.
 * @return 1 if the character is printable, 0 otherwise.
 */
int					ft_isprint(int c);

/**
 * @brief Checks if a character is a whitespace character.
 *
 * This function determines if the given character is a whitespace character.
 * Whitespace characters include space (' '), horizontal tab ('\t'),
 * vertical tab ('\v'), newline ('\n'), carriage return ('\r'),
 * and form feed ('\f').
 *
 * @param c The character to check.
 * @return 1 if the character is a whitespace character, 0 otherwise.
 */
int					ft_isspace(char c);

/**
 * @brief Converts an integer to a null-terminated string.
 *
 * This function takes an integer as input and converts it to a string
 * representation. It handles special cases such as zero and the minimum
 * integer value.
 *
 * @param n The integer to be converted.
 * @return A pointer to the resulting null-terminated string. Returns NULL if
 *         memory allocation fails.
 */
char				*ft_itoa(int n);

/**
 * @brief Adds a new element at the end of a linked list.
 *
 * This function takes a pointer to the first element of a linked list and a new
 * element to be added. If the list is empty, the new element becomes the first
 * element. Otherwise, the new element is added at the end of the list.
 *
 * @param lst A pointer to the first element of the list.
 * @param new The new element to be added to the list.
 */
void				ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Adds a new element at the beginning of a linked list.
 *
 * This function takes a pointer to the first element of a linked list and a new
 * element to be added. It sets the new element's next pointer to the current
 * first element and updates the list pointer to point to the new element.
 *
 * @param lst A double pointer to the first element of the list.
 * @param new The new element to be added to the list.
 */
void				ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Deletes a linked list.
 *
 * This function deletes and frees the given linked list and its content
 * using the function 'del' and free(3). The pointer to the list is set to NULL.
 *
 * @param lst A pointer to the pointer of the first element of the list.
 * @param del A pointer to the function used to delete the content of an
 *            element.
 */
void				ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief Deletes a single element from a linked list.
 *
 * This function takes a pointer to a list element and a function pointer
 * to a delete function. It applies the delete function to the content of
 * the list element and then frees the memory allocated for the element itself.
 *
 * @param lst A pointer to the list element to be deleted.
 * @param del A function pointer to a function that deletes the content of the
 *            list element.
 */
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief Retrieves the content of the node at a specified index in a linked
 * list.
 *
 * This function traverses the linked list until it reaches the node at the
 * given index and returns the content of that node. If the index is out of
 * bounds, it returns NULL.
 *
 * @param lst A pointer to the first node of the linked list.
 * @param index The zero-based index of the node whose content is to be
 *              retrieved.
 * @return The content of the node at the specified index, or NULL if the index
 *         is out of bounds.
 */
void				*ft_lstindex(t_list *lst, unsigned int index);

/**
 * @brief Iterates over a list and applies a function to each element.
 *
 * This function takes a linked list and a function pointer as arguments.
 * It iterates over each element of the list and applies the given function
 * to the content of each element.
 *
 * @param lst A pointer to the first element of the list.
 * @param f A function pointer to a function that takes a void pointer as an
 *          argument.
 */
void				ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Returns the last element of the list.
 *
 * This function traverses the linked list starting from the given node
 * and returns the last node in the list.
 *
 * @param lst A pointer to the first node of the linked list.
 * @return A pointer to the last node of the linked list,
	or NULL if the list is empty.
 */
t_list				*ft_lstlast(t_list *lst);

/**
 * @brief Contains the implementation of the ft_lstmap function.
 *
 * This function applies a given function to each element of a linked list,
 * creating a new list with the results. If an element creation fails,
 * the function clears the new list and returns NULL.
 *
 * @param lst The pointer to the first element of the list.
 * @param f The function to apply to each element's content.
 * @param del The function to delete the content of an element if needed.
 * @return A new list with the results of applying the function f to each
 *         element's content NULL if memory allocation fails for any element.
 *
 * @note The function f must return a copy of the content of each node.
 *       Otherwise both original and new list will point to the same content.
 */
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/**
 * @brief Allocates and initializes a new list node.
 *
 * This function creates a new list node with the given content. It allocates
 * memory for the node, sets its content to the provided value, and initializes
 * the next pointer to NULL.
 *
 * @param content The content to store in the new list node.
 * @return A pointer to the newly created list node, or NULL if memory
 *         allocation fails.
 */
t_list				*ft_lstnew(void *content);

/**
 * @brief Counts the number of elements in a linked list.
 *
 * This function iterates through the linked list pointed to by `lst` and counts
 * the number of elements in the list.
 *
 * @param lst A pointer to the first element of the linked list.
 * @return The number of elements in the linked list.
 */
int					ft_lstsize(t_list *lst);

/**
 * @brief Frees a dynamically allocated 2D array.
 *
 * This function frees each element of a 2D array and then frees the array
 * itself.
 * It can handle arrays where the size is known or unknown.
 *
 * @param array The 2D array to be freed.
 * @param size The number of elements in the array. If size is 0, the function
 *             will free elements until a NULL pointer is encountered.
 */
void				ft_matrix_free(void **array, size_t size);

/**
 * @brief Calculates the length of a null-terminated array of pointers.
 *
 * This function iterates through the array of pointers until it encounters
 * a null pointer, counting the number of elements in the array.
 *
 * @param array A null-terminated array of pointers.
 * @return The number of elements in the array, excluding the null pointer.
 */
size_t				ft_matrix_len(void **array);

/**
 * @brief Finds the maximum value in a specified column of a 2D array.
 *
 * This function iterates through a specified column of a 2D array and returns
 * the maximum value found in that column.
 *
 * @param array A pointer to the 2D array of doubles.
 * @param size The number of rows in the 2D array.
 * @param pos The index of the column to search for the maximum value.
 * @return The maximum value found in the specified column.
 */
double				ft_matrix_maxcol(double **array, size_t size, size_t pos);

/**
 * @brief Finds the minimum value in a specified column of a 2D array.
 *
 * This function iterates through a 2D array and finds the minimum value
 * in the specified column (pos).
 *
 * @param array A pointer to the 2D array of doubles.
 * @param size The number of rows in the 2D array.
 * @param pos The column index to search for the minimum value.
 * @return The minimum value found in the specified column.
 */
double				ft_matrix_mincol(double **array, size_t size, size_t pos);

/**
 * Searches for the first occurrence of a byte in a block of memory.
 *
 * @param s Pointer to the block of memory to be searched.
 * @param c Value to be searched for, treated as an unsigned char.
 * @param n Number of bytes to be searched.
 *
 * @return Pointer to the first occurrence of the byte if found,
 *         or NULL if not found.
 */
void				*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Compares two memory blocks.
 *
 * The `memcmp` function compares the first `n` bytes of the memory areas `s1`
 * and `s2`.
 *
 * @param s1 Pointer to the first memory block.
 * @param s2 Pointer to the second memory block.
 * @param n Number of bytes to compare.
 *
 * @return An integer less than, equal to, or greater than zero if the first `n`
 *         bytes of `s1` are found, respectively, to be less than, to match, or
 *         be greater than the first `n` bytes of `s2`.
 */
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Copies a block of memory from a source address to a destination
 * address.
 *
 * This function copies the values of `n` bytes from the memory area pointed
 * to by `src` to the memory area pointed to by `dest`. The memory areas must
 * not overlap.
 *
 * @param dest Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n Number of bytes to be copied.
 * @return Pointer to the destination memory area (`dest`).
 */
void				*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Joins two memory blocks into a new memory block.
 *
 * This function allocates a new memory block and copies the contents of the
 * first memory block (m1) followed by the contents of the second memory
 * block (m2) into the new memory block.
 *
 * @param m1 Pointer to the first memory block.
 * @param n1 Size of the first memory block in bytes.
 * @param m2 Pointer to the second memory block.
 * @param n2 Size of the second memory block in bytes.
 * @return Pointer to the newly allocated memory block containing the joined
 * contents of m1 and m2. Returns NULL if both m1 and m2 are NULL or if memory
 * allocation fails.
 */
void				*ft_memjoin(void *m1, size_t n1, const void *m2, size_t n2);

/**
 * @brief Copies a block of memory, allowing overlapping regions.
 *
 * This function copies `n` bytes from the memory area pointed to by `src`
 * to the memory area pointed to by `dest`. If the `dest` memory area is located
 * after the `src` memory area, the function uses `ft_memcpy` to perform the
 * copy in a safe manner. Otherwise, it performs the copy by iterating backwards
 * from the end of the memory areas.
 *
 * @param dest Pointer to the destination memory area where the content is
 *             to be copied.
 * @param src Pointer to the source of data to be copied.
 * @param n Number of bytes to copy.
 * @return A pointer to the destination memory area (`dest`).
 * @see ft_memcpy
 */
void				*ft_memmove(void *dest, const void *src, size_t n);

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
void				*ft_memset(void *s, int c, size_t n);

/**
 * @file ft_mindbl.c
 * @brief Finds the position of the minimum value in an array of doubles.
 *
 * This function iterates through an array of doubles and returns the index
 * of the smallest value found in the array.
 *
 * @param array A pointer to the array of doubles.
 * @param size The number of elements in the array.
 * @return The index of the minimum value in the array.
 */
size_t				ft_mindbl(double *array, size_t size);

/**
 * ft_minint - Finds the position of the minimum integer in an array.
 * @array: The array of integers.
 * @size: The size of the array.
 *
 * This function iterates through the given array to find the position
 * of the smallest integer. It returns the index of the minimum integer.
 *
 * @return: The index of the minimum integer in the array.
 * @todo: Try better search algorithm (Ex: binary search)
 */
size_t				ft_minint(int *array, size_t size);

/**
 * @brief A function that does nothing with the given content.
 *
 * This function is a placeholder that takes a single argument of type void*
 * and does nothing with it. It is useful in situations where a function
 * pointer is required, but no operation is needed.
 *
 * @param content A pointer to any type of data. This parameter is not used.
 */
void				ft_nothing(void *content);

/**
 * @brief Custom perror function with error and exit handling.
 *
 * This function prints a custom error message using perror, sets the errno
 * value if provided, and exits the program with a specified exit value.
 *
 * @param message The custom error message to be printed.
 * @param err_val The error value to set errno to. If 0, errno is not modified.
 * @param exit_value The value to exit the program with. If 0,
 *                   the program does not exit.
 */
void				ft_perror(char message[], char err_val, char exit_value);

/**
 * @brief Writes a character to the specified file descriptor.
 *
 * This function takes a character and a file descriptor as arguments and writes
 * the character to the given file descriptor.
 *
 * @param c The character to be written.
 * @param fd The file descriptor to which the character will be written.
 */
void				ft_putchar_fd(char c, int fd);

/**
 * @brief Outputs the string 's' to the given file descriptor followed by a
 * newline.
 *
 * This function writes the string 's' to the file descriptor specified by 'fd',
 * and then writes a newline character to the same file descriptor.
 *
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
 */
void				ft_putendl_fd(char *s, int fd);

/**
 * @brief Outputs the integer n to the given file descriptor.
 *
 * This function converts the integer n to a string using ft_itoa and then
 * writes the string to the file descriptor specified by fd using ft_putstr_fd.
 *
 * @param n The integer to be output.
 * @param fd The file descriptor on which to write.
 */
void				ft_putnbr_fd(int n, int fd);

/**
 * @brief Writes a string to the given file descriptor.
 *
 * This function takes a string and a file descriptor as arguments and writes
 * the string to the specified file descriptor using the ft_putchar_fd function.
 *
 * @param s The string to be written.
 * @param fd The file descriptor to which the string will be written.
 */
void				ft_putstr_fd(char *s, int fd);

/**
 * @brief Reallocates a memory block with a new size.
 *
 * This function reallocates a given memory block to a new size. If the new size
 * is zero and the pointer is not NULL, the memory block is freed. If the
 * pointer is NULL, the function behaves like malloc. If the allocation fails,
 * NULL is returned.
 *
 * @param ptr Pointer to the memory block to be reallocated. If NULL,
 *            a new block is allocated.
 * @param old_size The size of the original memory block.
 * @param size The new size for the memory block.
 * @return A pointer to the newly allocated memory block, or NULL if the
 *         allocation fails.
 */
void				*ft_realloc(void *ptr, size_t old_size, size_t size);

/**
 * @brief Splits a string into an array of substrings based on a delimiter.
 *
 * This function takes a string `s` and a delimiter character `c`, and splits
 * the string into an array of substrings. The substrings are allocated
 * dynamically and stored in an null endeded array of strings,
 * which is returned.
 *
 * @param s The input string to be split.
 * @param c The delimiter character used to split the string.
 * @return A pointer to an array of strings (substrings) resulting
 *         from the split. If memory allocation fails or any other error occurs,
 *         NULL is returned.
 */
char				**ft_split(char const *s, char c);

/**
 * @brief Splits a string into substrings based on a delimiter, keeping the
 *        delimiter as separate tokens.
 *
 * This function splits the input string `s` into substrings using the delimiter
 * character `c`. Unlike ft_split, this function keeps each occurrence of the
 * delimiter as a separate token in the result array.
 *
 * @param s The input string to be split.
 * @param c The delimiter character.
 * @return A pointer to the array of substrings, or NULL if memory
 *         allocation fails.
 */
char				**ft_splitkeep(char const *s, char c);

/**
 * @brief Splits a string into an array of substrings based on multiple
 *        delimiters.
 *
 * This function splits the input string s into an array of substrings,
 * using any of thecharacters in @cs as delimiters. The resulting array of
 * substrings is dynamically allocatedand must be freed by the caller.
 * The last element of the array is set to NULL.
 *
 * @param cs A string containing the delimiter characters.
 * @param s The input string to be split.
 * @return A pointer to the array of substrings, or NULL if memory
 *         allocation fails.
 */
char				**ft_splitm(char const *s, char *cs);

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
char				*ft_strchr(const char *s, int c);

/**
 * @brief Custom string search function.
 *
 * This function searches for the first occurrence of any character from the
 * array `c` in the string `s`. If a character from `c` is found in `s`, a
 * pointer to the character in `s` is returned. If no character from `c` is
 * found, NULL is returned.
 *
 * @param s The string to be searched.
 * @param c An array of integers representing the characters to search for.
 * @return A pointer to the first occurrence of any character from `c` in `s`,
 *         or NULL if no such character is found.
 *
 * @note The function allocates memory for an unsigned char array to store the
 *       characters from `c`. This memory is freed before the function returns.
 *       If memory allocation fails, the function returns NULL and prints an
 *       error message.
 */
char				*ft_strchrm(const char *s, char *c);

/**
 * @brief Duplicates a string.
 *
 * This function allocates sufficient memory for a copy of the string s,
 * does the copy, and returns a pointer to it. The memory allocated for the
 * new string is obtained with malloc, and can be freed with free.
 *
 * @param s The string to duplicate.
 * @return A pointer to the duplicated string, or NULL if insufficient memory
 *         was available.
 */
char				*ft_strdup(const char *s);

/**
 * Inserts a substring into a source string between specified positions.
 *
 * @param src      The original source string.
 * @param start_pos Pointer to the start position in src where insertion begins
 *                  (inclusive).
 * @param end_pos   Pointer to the end position in src where insertion ends
 *                  (exclusive).
 * @param insert    The string to insert between start_pos and end_pos.
 * @return          A newly allocated string with the inserted substring.
 *                  The caller is responsible for freeing the returned string.
 *
 * @note
 * - Duplicates the part of src before start_pos (inclusive), appends insert,
 *   then appends the part of src from end_pos onward.
 * - Assumes start_pos and end_pos are valid pointers within src, and
 *   start_pos <= end_pos.
 */
char				*ft_strinsert(char *src, char *start_pos, char *end_pos,
						char *insert);

/**
 * @brief Applies a function to each character of a string, passing its index.
 *
 * This function iterates over each character of the string `s` and applies
 * the function `f` to each character, passing the character's index and a
 * pointer to the character itself.
 *
 * @param s The string to iterate over.
 * @param f The function to apply to each character. It takes two parameters:
 *          an unsigned int representing the character's index, and a char*
 *          pointing to the character itself.
 *
 * @note If either `s` or `f` is NULL, the function does nothing.
 */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

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
char				*ft_strjoin(char const *s1, char const *s2);

/**
 * Appends the string pointed to by `src` to the end of the string pointed to
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
size_t				ft_strlcat(char *dst, const char *src, size_t size);

/**
 * @brief Copies a string to a destination buffer with a specified size.
 *
 * This function copies the string pointed to by `src` to the buffer pointed
 * to by `dst`. The copy operation will stop when either the null-terminating
 * character of `src` is reached or when `size - 1` characters have been copied
 * to `dst`. The resulting string in `dst` will always be null-terminated.
 *
 * @param dst The destination buffer where the string will be copied to.
 * @param src The source string to be copied.
 * @param size The size of the destination buffer.
 * @return The length of the source string.
 */
size_t				ft_strlcpy(char *dst, const char *src, size_t size);

/**
 * Calculates the length of a null-terminated string.
 *
 * @param str The string to calculate the length of.
 * @return The length of the string.
 */
size_t				ft_strlen(const char *str);

/**
 * @brief Applies a function to each character of a string to create a new
 * string.
 *
 * This function takes a string `s` and a function `f` as arguments. It applies
 * the function `f` to each character of the string `s` to create a new string
 * (with malloc) resulting from successive applications of `f`.
 *
 * @param s The string on which to iterate.
 * @param f The function to apply to each character of `s` and its index.
 * @return A new string resulting from the successive applications of `f`.
 *         Returns NULL if memory allocation fails.
 * @note If either `s` or `f` is NULL, the function does nothing.
 */
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Compares two strings up to a specified number of characters.
 *
 * The ft_strncmp() function compares the string pointed to by s1 to the string
 * pointed to by s2, up to the maximum of n characters. The comparison is done
 * case-sensitive and stops if a difference is found or if the end of either
 * string is reached.
 *
 * @param s1 The first string to be compared.
 * @param s2 The second string to be compared.
 * @param n The maximum number of characters to compare.
 * @return An integer greater than, equal to, or less than 0, depending on
 * whether the string pointed to by s1 is greater than, equal to, or less than
 * the string pointed to by s2.
 */
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Duplicates up to n characters from the given string.
 *
 * This function allocates memory and duplicates up to n characters from the
 * input string `s`. If `n` is greater than the length of the string, the
 * entire string is duplicated. The duplicated string is null-terminated.
 *
 * @param s The input string to duplicate.
 * @param n The maximum number of characters to duplicate.
 * @return A pointer to the newly allocated string, or NULL if memory
 * allocation fails.
 */
char				*ft_strndup(const char *s, size_t n);

/**
 * Locates the first occurrence of the null-terminated string 'little'
 * within the null-terminated string 'big', where not more than 'len'
 * characters are searched.
 *
 * @param big The string to be searched.
 * @param little The string to search for.
 * @param len The maximum number of characters to search.
 *
 * @return If 'little' is an empty string,
	'big' is returned; if 'little' occurs
 *         nowhere in 'big', NULL is returned; otherwise, a pointer to the first
 *         character of the first occurrence of 'little' is returned.
 */
char				*ft_strnstr(const char *big, const char *little,
						size_t len);

/**
 * @brief Searches for the last occurrence of a character in a string.
 *
 * This function searches for the last occurrence of the character 'c' in the
 * string 's'. If the character is found, a pointer to the last occurrence is
 * returned. If the character is not found and 'c' is the null terminator, a
 * pointer to the null terminator of 's' is returned. If the character is not
 * found, it returns NULL.
 *
 * @param s The string to be searched.
 * @param c The character to be found.
 * @return A pointer to the last occurrence of the character in the string, or
 *         NULL if not found.
 */
char				*ft_strrchr(const char *s, int c);

/**
 * @brief Counts the number of tokens in a string separated by any of the
 *        characters in the given set.
 * This function scans the input string "s" and counts the number of tokens
 * separated by any of the characters in the set "cs". A token is defined as a
 * contiguous sequence of characters that are not in the set "cs".
 *
 * @param s: The input string to be tokenized.
 * @param cs: The set of delimiter characters.
 *
 * @return The number of tokens found in the input string.
 */
size_t				ft_strtkns(char const *s, char *cs);

/**
 * @brief Trims characters from the beginning and end of a string.
 *
 * This function takes a string `s1` and a set of characters `set`, and
 * returns a new string with all characters in `set` removed from the
 * beginning and end of `s1`.
 *
 * @param s1 The original string to be trimmed.
 * @param set The set of characters to be trimmed from the beginning and
 * end of `s1`.
 * @return A new string with the specified characters trimmed from the
 * beginning and end. Returns NULL if memory allocation fails.
 */
char				*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Extracts a substring from a given string.
 *
 * This function allocates (with malloc) and returns a substring from the
 * string `s`. The substring begins at index `start` and is of maximum size
 * `len`.
 *
 * @param s The string from which to extract the substring.
 * @param start The starting index of the substring in the string `s`.
 * @param len The maximum length of the substring.
 * @return A pointer to the newly allocated substring, or NULL if the
 *         allocation fails or if `start` is greater than or equal to the
 *         length of `s`.
 */
char				*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Converts a lowercase character to lowercase.
 *
 * This function takes a character as input and checks if it is
 * a uppercase letter. If it is, the function converts it to lowercase by
 * adding 32 from its ASCII value. If the character is not a uppercase letter,
 * it remains unchanged.
 *
 * @param c The character to be converted.
 * @return The uppercase version of the character if it is a lowercase letter,
 *         otherwise the character itself.
 */
int					ft_tolower(int c);

/**
 * @brief Converts a lowercase character to uppercase.
 *
 * This function takes a character as input and checks if it is
 * a lowercase letter. If it is, the function converts it to uppercase by
 * subtracting 32 from its ASCII value. If the character is not a lowercase
 * letter, it remains unchanged.
 *
 * @param c The character to be converted.
 * @return The uppercase version of the character if it is a lowercase letter,
 *         otherwise the character itself.
 */
int					ft_toupper(int c);

/**
 * Converts an integer pointer to a string representation in a specified base.
 *
 * @param nbr The integer pointer to be converted.
 * @param base The base to be used for conversion. It should be a string
 * containing all the characters representing the digits of the base.
 */
char				*ft_uintptrtob(uintptr_t nbr, char *base);

/**
 * @brief Converts an unsigned integer to a null-terminated string.
 *
 * This function takes an unsigned integer and converts it to a string
 * representation. The resulting string is dynamically allocated and
 * must be freed by the caller.
 *
 * @param n The unsigned integer to convert.
 * @return A pointer to the newly allocated string representing the number,
 *         or NULL if memory allocation fails.
 */
char				*ft_uitoa(unsigned int n);

/**
 * Converts an unsigned integer to a string representation in a specified base.
 *
 * @param nbr The unsigned integer to convert.
 * @param base The base to use for the conversion. This should be a string
 *             containing the characters representing the digits of the base
 *             (e.g., "0123456789ABCDEF" for base 16).
 * @return A pointer to the newly allocated string containing the base
 *         representation of the number. The caller is responsible for freeing
 *         the allocated memory.
 */
char				*ft_uitob(unsigned int nbr, char *base);

#endif
