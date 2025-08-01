/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:26:31 by pablo             #+#    #+#             */
/*   Updated: 2025/06/24 13:57:14 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// Códigos de escape ANSI para colores de texto
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"
# define BLACK   "\033[30m"

// Colores brillantes
# define BRIGHT_RED     "\033[91m"
# define BRIGHT_GREEN   "\033[92m"
# define BRIGHT_YELLOW  "\033[93m"
# define BRIGHT_BLUE    "\033[94m"
# define BRIGHT_MAGENTA "\033[95m"
# define BRIGHT_CYAN    "\033[96m"
# define BRIGHT_WHITE   "\033[97m"

// Estilos de texto
# define BOLD       "\033[1m"
# define UNDERLINE  "\033[4m"
# define ITALIC     "\033[3m"

// Colores de fondo
# define BG_RED     "\033[41m"
# define BG_GREEN   "\033[42m"
# define BG_YELLOW  "\033[43m"
# define BG_BLUE    "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN    "\033[46m"
# define BG_WHITE   "\033[47m"
# define BG_BLACK   "\033[40m"

// Reset - vuelve a los colores por defecto
# define RESET   "\033[0m"

#endif
