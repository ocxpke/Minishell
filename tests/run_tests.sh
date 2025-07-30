#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run_tests.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pablo <pablo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/30 19:30:00 by pablo             #+#    #+#              #
#    Updated: 2025/07/30 19:30:00 by pablo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Función para mostrar ayuda
show_help() {
    echo -e "${BLUE}Minishell Parser Test Runner${NC}"
    echo -e "${BLUE}=============================${NC}"
    echo ""
    echo "Uso: $0 [opción] [argumentos]"
    echo ""
    echo "Opciones:"
    echo -e "  ${GREEN}build${NC}              - Compilar el suite de pruebas"
    echo -e "  ${GREEN}test${NC}               - Ejecutar el menú interactivo de pruebas"
    echo -e "  ${GREEN}quick [input]${NC}      - Probar un input específico rápidamente"
    echo -e "  ${GREEN}batch${NC}              - Ejecutar todas las pruebas automáticamente"
    echo -e "  ${GREEN}valgrind${NC}           - Ejecutar con detección de memory leaks"
    echo -e "  ${GREEN}clean${NC}              - Limpiar archivos compilados"
    echo -e "  ${GREEN}help${NC}               - Mostrar esta ayuda"
    echo ""
    echo "Ejemplos:"
    echo "  $0 build"
    echo "  $0 quick 'ls -la | grep test'"
    echo "  $0 test"
    echo ""
}

# Función para compilar
build() {
    echo -e "${YELLOW}Compilando suite de pruebas...${NC}"
    if make -f Makefile.test; then
        echo -e "${GREEN}✓ Compilación exitosa${NC}"
        return 0
    else
        echo -e "${RED}✗ Error en la compilación${NC}"
        return 1
    fi
}

# Función para ejecutar prueba rápida
quick_test() {
    if [ -z "$1" ]; then
        echo -e "${RED}Error: Debes proporcionar un input para la prueba rápida${NC}"
        echo "Ejemplo: $0 quick 'ls -la | grep test'"
        return 1
    fi

    echo -e "${YELLOW}Probando input: ${BLUE}\"$1\"${NC}"
    echo -e "${YELLOW}================================${NC}"

    if [ ! -f "./test_parser" ]; then
        echo -e "${YELLOW}Compilando primero...${NC}"
        if ! build; then
            return 1
        fi
    fi

    ./test_parser "$1"
}

# Función para ejecutar todas las pruebas automáticamente
batch_test() {
    echo -e "${YELLOW}Ejecutando todas las pruebas automáticamente...${NC}"

    if [ ! -f "./test_parser" ]; then
        echo -e "${YELLOW}Compilando primero...${NC}"
        if ! build; then
            return 1
        fi
    fi

    # Lista de comandos de prueba
    test_commands=(
        "ls"
        "ls -la"
        "echo hello"
        "ls | grep test"
        "cat file.txt | head -n 5"
        "ls > output.txt"
        "cat < input.txt"
        "echo hello >> file.txt"
        "cat << EOF"
        "echo 'hello world'"
        "echo \"hello world\""
        "echo \$HOME"
        "echo \$USER"
        "echo \$?"
        "ls -la | grep 'test' > output.txt"
        "echo \"Hello \$USER\" | cat > greeting.txt"
        ""
        "   "
        "echo 'unclosed"
        "ls | | cat"
    )

    echo -e "${BLUE}Ejecutando ${#test_commands[@]} pruebas...${NC}"

    for i in "${!test_commands[@]}"; do
        echo -e "\n${YELLOW}[Prueba $((i+1))/${#test_commands[@]}] Input: \"${test_commands[i]}\"${NC}"
        echo "----------------------------------------"
        ./test_parser "${test_commands[i]}"
        echo "----------------------------------------"
        sleep 1
    done

    echo -e "\n${GREEN}✓ Pruebas batch completadas${NC}"
}

# Función para ejecutar con valgrind
valgrind_test() {
    echo -e "${YELLOW}Ejecutando con Valgrind...${NC}"

    if [ ! -f "./test_parser" ]; then
        echo -e "${YELLOW}Compilando primero...${NC}"
        if ! build; then
            return 1
        fi
    fi

    make -f Makefile.test valgrind
}

# Función para limpiar
clean() {
    echo -e "${YELLOW}Limpiando archivos...${NC}"
    make -f Makefile.test fclean
    echo -e "${GREEN}✓ Limpieza completada${NC}"
}

# Función para ejecutar tests interactivos
interactive_test() {
    echo -e "${YELLOW}Iniciando suite de pruebas interactivo...${NC}"

    if [ ! -f "./test_parser" ]; then
        echo -e "${YELLOW}Compilando primero...${NC}"
        if ! build; then
            return 1
        fi
    fi

    ./test_parser
}

# Verificar si estamos en el directorio correcto
if [ ! -f "test_parser.c" ] || [ ! -f "Makefile.test" ]; then
    echo -e "${RED}Error: No se encontraron los archivos de prueba${NC}"
    echo "Asegúrate de estar en el directorio raíz del proyecto minishell"
    exit 1
fi

# Procesar argumentos
case "$1" in
    "build")
        build
        ;;
    "test")
        interactive_test
        ;;
    "quick")
        quick_test "$2"
        ;;
    "batch")
        batch_test
        ;;
    "valgrind")
        valgrind_test
        ;;
    "clean")
        clean
        ;;
    "help"|"--help"|"-h"|"")
        show_help
        ;;
    *)
        echo -e "${RED}Opción desconocida: $1${NC}"
        echo ""
        show_help
        exit 1
        ;;
esac
