/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:30:00 by pablo             #+#    #+#             */
/*   Updated: 2025/07/30 19:46:20 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Estructura para definir casos de prueba
 */
typedef struct s_test_case
{
	char	*input;
	char	*description;
}	t_test_case;

/**
 * @brief Función auxiliar para imprimir el encabezado de una prueba
 */
static void	print_test_header(int test_num, const char *description, const char *input)
{
	printf("\n");
	printf("========================================\n");
	printf("TEST %d: %s\n", test_num, description);
	printf("Input: \"%s\"\n", input);
	printf("========================================\n");
}

/**
 * @brief Función auxiliar para imprimir el pie de una prueba
 */
static void	print_test_footer(void)
{
	printf("========================================\n");
	printf("Press ENTER to continue...");
	getchar();
}

/**
 * @brief Ejecuta una prueba individual
 */
static void	run_test(int test_num, t_test_case test)
{
	print_test_header(test_num, test.description, test.input);
	parse(test.input);
	print_test_footer();
}

/**
 * @brief Casos de prueba para comandos simples
 */
static void	test_simple_commands(void)
{
	t_test_case tests[] = {
		{"ls", "Comando simple sin argumentos"},
		{"ls -la", "Comando con argumentos"},
		{"echo hello", "Comando con argumento simple"},
		{"pwd", "Comando built-in"},
		{"cd /home", "Comando built-in con argumento"},
		{"/bin/ls", "Comando con ruta absoluta"},
		{"./test", "Comando con ruta relativa"},
		{"", "String vacío"},
		{"   ", "Solo espacios"},
		{NULL, NULL}
	};

	int i = 0;
	printf("\n=== TESTING SIMPLE COMMANDS ===\n");
	while (tests[i].input)
	{
		run_test(i + 1, tests[i]);
		i++;
	}
}

/**
 * @brief Casos de prueba para pipes
 */
static void	test_pipes(void)
{
	t_test_case tests[] = {
		{"ls | grep test", "Pipe simple"},
		{"cat file.txt | head -n 5 | tail -n 2", "Múltiples pipes"},
		{"echo hello | cat", "Pipe con echo"},
		{"ls -la | wc -l", "Pipe con opciones"},
		{"|", "Solo pipe"},
		{"ls |", "Pipe al final"},
		{"| ls", "Pipe al inicio"},
		{"ls || cat", "Doble pipe (debería fallar)"},
		{NULL, NULL}
	};

	int i = 0;
	printf("\n=== TESTING PIPES ===\n");
	while (tests[i].input)
	{
		run_test(i + 1, tests[i]);
		i++;
	}
}

/**
 * @brief Casos de prueba para redirecciones
 */
static void	test_redirections(void)
{
	t_test_case tests[] = {
		{"ls > output.txt", "Redirección de salida"},
		{"cat < input.txt", "Redirección de entrada"},
		{"echo hello >> file.txt", "Redirección append"},
		{"cat << EOF", "Heredoc"},
		{"ls > file1.txt < file2.txt", "Múltiples redirecciones"},
		{"echo test > file.txt | cat", "Redirección con pipe"},
		{"> output.txt ls", "Redirección antes del comando"},
		{"< input.txt cat", "Redirección de entrada antes del comando"},
		{">> file.txt echo hello", "Append antes del comando"},
		{"<< EOF cat", "Heredoc antes del comando"},
		{"< input.txt > output.txt cat", "Múltiples redirecciones antes del comando"},
		{"> output.txt < input.txt cat", "Redirecciones mixtas antes del comando"},
		{"< file1.txt cat > file2.txt", "Redirección antes y después del comando"},
		{"> out.txt echo hello > out2.txt", "Múltiples redirecciones de salida"},
		{"< in1.txt < in2.txt cat", "Múltiples redirecciones de entrada"},
		{">", "Solo redirección"},
		{"<", "Solo redirección de entrada"},
		{">>", "Solo append"},
		{"<<", "Solo heredoc"},
		{NULL, NULL}
	};

	int i = 0;
	printf("\n=== TESTING REDIRECTIONS ===\n");
	while (tests[i].input)
	{
		run_test(i + 1, tests[i]);
		i++;
	}
}

/**
 * @brief Casos de prueba para quotes
 */
static void	test_quotes(void)
{
	t_test_case tests[] = {
		{"echo 'hello world'", "Single quotes"},
		{"echo \"hello world\"", "Double quotes"},
		{"echo 'hello' world", "Single quotes parciales"},
		{"echo \"hello\" world", "Double quotes parciales"},
		{"echo 'hello \"nested\" world'", "Quotes anidadas"},
		{"echo \"hello 'nested' world\"", "Quotes anidadas invertidas"},
		{"echo 'unclosed quote", "Quote sin cerrar"},
		{"echo \"unclosed quote", "Double quote sin cerrar"},
		{"echo ''", "Quotes vacías"},
		{"echo \"\"", "Double quotes vacías"},
		{"echo 'multiple' 'quotes'", "Múltiples quotes"},
		{NULL, NULL}
	};

	int i = 0;
	printf("\n=== TESTING QUOTES ===\n");
	while (tests[i].input)
	{
		run_test(i + 1, tests[i]);
		i++;
	}
}

/**
 * @brief Casos de prueba para variables de entorno
 */
static void	test_environment_variables(void)
{
	t_test_case tests[] = {
		{"echo $HOME", "Variable de entorno simple"},
		{"echo $USER", "Variable USER"},
		{"echo $PATH", "Variable PATH"},
		{"echo $?", "Exit status"},
		{"echo $HOME/documents", "Variable con concatenación"},
		{"echo ${HOME}", "Variable con llaves"},
		{"echo $NONEXISTENT", "Variable inexistente"},
		{"echo '$HOME'", "Variable en single quotes (no expandir)"},
		{"echo \"$HOME\"", "Variable en double quotes (expandir)"},
		{"echo $HOME$USER", "Múltiples variables"},
		{"$HOME/bin/ls", "Variable como comando"},
		{NULL, NULL}
	};

	int i = 0;
	printf("\n=== TESTING ENVIRONMENT VARIABLES ===\n");
	while (tests[i].input)
	{
		run_test(i + 1, tests[i]);
		i++;
	}
}

/**
 * @brief Casos de prueba complejos que combinan múltiples características
 */
static void	test_complex_cases(void)
{
	t_test_case tests[] = {
		{"ls -la | grep 'test' > output.txt", "Pipe + quotes + redirección"},
		{"echo \"Hello $USER\" | cat > greeting.txt", "Variables + quotes + pipe + redirección"},
		{"cat < input.txt | grep 'pattern' >> results.txt", "Múltiples redirecciones + pipe"},
		{"ls '$HOME' | wc -l", "Variables en quotes + pipe"},
		{"echo 'test' | cat | wc -l > count.txt", "Múltiples pipes + redirección"},
		{"cat << 'EOF' | grep test", "Heredoc con quotes + pipe"},
		{"/bin/echo \"$HOME/test\" > '$USER.txt'", "Ruta absoluta + variables + quotes + redirección"},
		{"   ls   -la   |   grep   test   ", "Espacios extra"},
		{"< input.txt cat | > output.txt grep pattern", "Redirecciones antes de comandos con pipes"},
		{"> temp.txt echo hello | < temp.txt cat", "Redirecciones mixtas con pipes"},
		{"< file1.txt cat | grep test | > file2.txt sort", "Múltiples pipes con redirecciones"},
		{">> log.txt echo start | cat | >> log.txt tee", "Append con pipes"},
		{NULL, NULL}
	};

	int i = 0;
	printf("\n=== TESTING COMPLEX CASES ===\n");
	while (tests[i].input)
	{
		run_test(i + 1, tests[i]);
		i++;
	}
}

/**
 * @brief Casos de prueba para situaciones de error
 */
static void	test_error_cases(void)
{
	t_test_case tests[] = {
		{"echo 'unclosed", "Quote sin cerrar"},
		{"echo \"unclosed", "Double quote sin cerrar"},
		{"ls | | cat", "Doble pipe"},
		{"ls > > file.txt", "Doble redirección"},
		{"< > file.txt", "Redirecciones sin comando"},
		{"", "Comando vacío"},
		{"   \t   ", "Solo whitespace"},
		{"ls ><< file.txt", "Redirecciones combinadas incorrectamente"},
		{NULL, NULL}
	};

	int i = 0;
	printf("\n=== TESTING ERROR CASES ===\n");
	while (tests[i].input)
	{
		run_test(i + 1, tests[i]);
		i++;
	}
}

/**
 * @brief Función principal del programa de pruebas
 */
int	main(int argc, char **argv)
{
	int choice;

	if (argc > 1)
	{
		// Modo de prueba específica
		printf("Testing specific input: \"%s\"\n", argv[1]);
		parse(argv[1]);
		return (0);
	}

	// Menú interactivo
	while (1)
	{
		printf("\n=== MINISHELL PARSER TEST SUITE ===\n");
		printf("1. Test Simple Commands\n");
		printf("2. Test Pipes\n");
		printf("3. Test Redirections\n");
		printf("4. Test Quotes\n");
		printf("5. Test Environment Variables\n");
		printf("6. Test Complex Cases\n");
		printf("7. Test Error Cases\n");
		printf("8. Run All Tests\n");
		printf("9. Custom Input\n");
		printf("0. Exit\n");
		printf("Choose an option: ");

		if (scanf("%d", &choice) != 1)
		{
			printf("Invalid input. Please enter a number.\n");
			while (getchar() != '\n'); // Limpiar buffer
			continue;
		}
		getchar(); // Consumir el newline

		switch (choice)
		{
			case 1:
				test_simple_commands();
				break;
			case 2:
				test_pipes();
				break;
			case 3:
				test_redirections();
				break;
			case 4:
				test_quotes();
				break;
			case 5:
				test_environment_variables();
				break;
			case 6:
				test_complex_cases();
				break;
			case 7:
				test_error_cases();
				break;
			case 8:
				test_simple_commands();
				test_pipes();
				test_redirections();
				test_quotes();
				test_environment_variables();
				test_complex_cases();
				test_error_cases();
				break;
			case 9:
				{
					char input[1024];
					printf("Enter custom input: ");
					if (fgets(input, sizeof(input), stdin))
					{
						// Remover el newline al final
						input[strcspn(input, "\n")] = 0;
						printf("Testing custom input: \"%s\"\n", input);
						parse(input);
						printf("Press ENTER to continue...");
						getchar();
					}
				}
				break;
			case 0:
				printf("Goodbye!\n");
				return (0);
			default:
				printf("Invalid option. Please try again.\n");
		}
	}

	return (0);
}
