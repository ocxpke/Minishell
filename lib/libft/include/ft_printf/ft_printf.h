/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:26:58 by pabmart2          #+#    #+#             */
/*   Updated: 2025/03/31 22:04:10 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include "libft.h"

/**
 * @typedef t_printer
 * @brief A function pointer type for functions that take a va_list argument
 *        and return an int.
 *
 * This typedef defines a function pointer type named t_printer. Functions of
 * this type are expected to take a single argument of type va_list and return
 * an int. This is typically used for functions that perform some kind of
 * formatted output or processing based on a variable argument list.
 *
 * @param va_list A variable argument list.
 * @return An integer result, typically indicating the number of characters
 *         printed or a status code.
 */
typedef int		(*t_printer)(va_list);

/**
 * @struct s_printers_list
 * @brief Structure to map a character to its corresponding printer function.
 *
 * This structure is used to associate a specific character with a function
 * that handles the conversion and printing of that character type.
 *
 * @param c Character representing the type of conversion.
 *
 * @param printer Function pointer to the printer function that handles the
 *                conversion.
 */
typedef struct s_printers_list
{
	char		c;
	t_printer	printer;
}				t_print_list;

/**
 * @file ft_printf.c
 * @brief Custom implementation of the printf function.
 *
 * This function mimics the behavior of the standard printf function, allowing
 * formatted output to the standard output.
 *
 * @param str The format string containing the text to be written to stdout.
 *            It can optionally contain embedded format specifiers that will
 *            be replaced by the values specified in subsequent arguments.
 * @param ... The variable arguments to be formatted and printed according to
 *            the format specifiers in the format string.
 *
 * @return The total number of characters written to the standard output.
 *
 */
int				ft_printf(char const *str, ...) __attribute__((format(printf, 1,
							2)));

/**
 * @brief Checks and returns the appropriate printer function for a given
 *        character.
 *
 * This function iterates through a global list of character-function pairs
 * (g_print_list) and returns the corresponding function if the character
 * matches one in the list.
 *
 * @param c The character to check against the list of printer functions.
 * @return The corresponding printer function if found, otherwise NULL.
 */
t_printer		check_printer(const char c);

/****************************** PRINTERS **************************************/

/**
 * @brief Prints a character from a variadic argument list.
 *
 * This function retrieves a character from the provided variadic argument
 * list, prints it to the standard output using ft_putchar_fd, and returns 1.
 *
 * @param arg The variadic argument list containing the character to print.
 * @return Always returns 1.
 */
int				c_printer(va_list arg);

/**
 * @brief Prints a string from a variadic argument list.
 * @param arg The variadic argument list containing the string to print.
 *
 * This function retrieves a string from the provided variadic argument list,
 * prints it to the standard output using ft_putstr_fd, and returns the length
 * of the string.
 *
 * @return The length of the printed string.
 */
int				s_printer(va_list arg);

/**
 * @brief Prints a pointer address in hexadecimal format.
 *
 * This function retrieves a pointer from the provided va_list, converts it
 * to a hexadecimal string representation, and prints it prefixed with "0x".
 * It returns the total number of characters printed, including the "0x" prefix.
 *
 * @param arg A va_list containing the pointer to be printed.
 * Return: The number of characters printed.
 */
int				p_printer(va_list arg);

/**
 * @brief Prints an integer argument as a string.
 *
 * This function retrieves an integer from the provided va_list,
 * converts it to a string using ft_itoa, and prints it to the
 * standard output using ft_putstr_fd. It returns the length of
 * the printed string.
 *
 * @param arg A va_list containing the integer to be printed.
 * Return: The length of the printed string.
 */
int				di_printer(va_list arg);

/**
 * @brief Prints an unsigned integer from a variable argument list.
 *
 * This function retrieves an unsigned integer from the provided variable
 * argument list, converts it to a string using ft_uitoa, and prints it to
 * the standard output using ft_putstr_fd. It returns the length of the
 * printed string.
 *
 * @param arg The variable argument list containing the unsigned integer
 *            to print.
 * @return The length of the printed string.
 */
int				u_printer(va_list arg);

/**
 * @brief Prints an unsigned integer in lowercase hexadecimal format.
 *
 * This function retrieves an unsigned integer from the provided va_list,
 * converts it to a string in lowercase hexadecimal format, and prints it
 * to the standard output. It returns the length of the printed string.
 *
 * @param arg A va_list containing the unsigned integer to be printed.
 * @return The length of the printed string.
 */
int				x_low_printer(va_list arg);

/**
 * @brief Prints an unsigned integer in uppercase hexadecimal format.
 *
 * This function retrieves an unsigned integer from the provided va_list,
 * converts it to a string in uppercase hexadecimal format, and prints it
 * to the standard output. It returns the length of the printed string.
 *
 * @param arg A va_list containing the unsigned integer to be printed.
 * @return The length of the printed string.
 */
int				x_up_printer(va_list arg);

/**
 * @brief - Prints a percent sign.
 *
 * This function prints a percent sign '%' to the standard output.
 * @param arg: A va_list of arguments (unused in this function).
 * @return Always returns 1
 */
int				prct_printer(va_list arg);

/*******************************LIBFT******************************************/

/**
 * Sets the first n bytes of the memory pointed to by s to zero.
 *
 * @param s Pointer to the memory to be zeroed.
 * @param n Number of bytes to be zeroed.
 */
void			ft_bzero(void *s, size_t n);

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
void			*ft_calloc(size_t nmemb, size_t size);

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
char			*ft_itoa(int n);

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
void			*ft_memset(void *s, int c, size_t n);

/**
 * @brief Writes a character to the specified file descriptor.
 *
 * This function takes a character and a file descriptor as arguments and writes
 * the character to the given file descriptor.
 *
 * @param c The character to be written.
 * @param fd The file descriptor to which the character will be written.
 */
void			ft_putchar_fd(char c, int fd);

/**
 * @brief Writes a string to the given file descriptor.
 *
 * This function takes a string and a file descriptor as arguments and writes
 * the string to the specified file descriptor using the ft_putchar_fd function.
 *
 * @param s The string to be written.
 * @param fd The file descriptor to which the string will be written.
 */
void			ft_putstr_fd(char *s, int fd);

/**
 * Calculates the length of a null-terminated string.
 *
 * @param str The string to calculate the length of.
 * @return The length of the string, or 0 if the string is NULL.
 */
size_t			ft_strlen(const char *str);

/**
 * Converts an integer pointer to a string representation in a specified base.
 *
 * @param nbr The integer pointer to be converted.
 * @param base The base to be used for conversion. It should be a string
 * containing all the characters representing the digits of the base.
 */
char			*ft_uintptrtob(uintptr_t nbr, char *base);

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
char			*ft_uitoa(unsigned int n);

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
char			*ft_uitob(unsigned int nbr, char *base);

#endif
