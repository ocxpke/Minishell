# Minishell Parser Test Suite

Esta es una batería de pruebas comprehensiva para testear el parser de minishell.

## Archivos incluidos

- `test_parser.c` - Suite principal de pruebas con menú interactivo
- `Makefile.test` - Makefile específico para compilar las pruebas
- `run_tests.sh` - Script de conveniencia para ejecutar diferentes tipos de pruebas
- `TEST_README.md` - Este archivo

## Cómo usar

### Opción 1: Script de conveniencia (Recomendado)

```bash
# Mostrar ayuda
./run_tests.sh help

# Compilar el suite de pruebas
./run_tests.sh build

# Ejecutar menú interactivo
./run_tests.sh test

# Prueba rápida con input específico
./run_tests.sh quick "ls -la | grep test"

# Ejecutar todas las pruebas automáticamente
./run_tests.sh batch

# Ejecutar con valgrind para detectar memory leaks
./run_tests.sh valgrind

# Limpiar archivos compilados
./run_tests.sh clean
```

### Opción 2: Makefile directo

```bash
# Compilar
make -f Makefile.test

# Ejecutar pruebas interactivas
make -f Makefile.test test

# Probar input específico
make -f Makefile.test test-input

# Valgrind
make -f Makefile.test valgrind

# Limpiar
make -f Makefile.test clean
```

### Opción 3: Ejecución directa

```bash
# Compilar manualmente
gcc -Wall -Wextra -Werror -g -Iinclude -Ilib/libft/include -Ilib/libft/include/ft_get_next_line -Ilib/libft/include/ft_printf test_parser.c src/parse/*.c src/parse/utils/*.c src/main.c lib/libft/libft.a -o test_parser

# Ejecutar
./test_parser

# O con input específico
./test_parser "ls -la | grep test"
```

## Categorías de pruebas

### 1. Comandos Simples
- Comandos sin argumentos (`ls`)
- Comandos con argumentos (`ls -la`)
- Comandos built-in (`pwd`, `cd`)
- Rutas absolutas y relativas
- Casos edge (string vacío, solo espacios)

### 2. Pipes
- Pipes simples (`ls | grep test`)
- Múltiples pipes (`cat file | head -5 | tail -2`)
- Casos de error (pipes mal formados)

### 3. Redirecciones
- Redirección de salida (`ls > file.txt`)
- Redirección de entrada (`cat < file.txt`)
- Append (`echo hello >> file.txt`)
- Heredoc (`cat << EOF`)
- Múltiples redirecciones
- Casos de error

### 4. Quotes
- Single quotes (`'hello world'`)
- Double quotes (`"hello world"`)
- Quotes anidadas
- Quotes sin cerrar (casos de error)
- Quotes vacías

### 5. Variables de Entorno
- Variables simples (`$HOME`)
- Exit status (`$?`)
- Variables con concatenación (`$HOME/documents`)
- Variables en quotes
- Variables inexistentes

### 6. Casos Complejos
- Combinaciones de todas las características anteriores
- Casos con espacios extra
- Comandos largos y complejos

### 7. Casos de Error
- Sintaxis incorrecta
- Quotes sin cerrar
- Redirecciones mal formadas
- Pipes incorrectos

## Características del suite

- **Menú interactivo**: Permite elegir qué categoría de pruebas ejecutar
- **Pruebas paso a paso**: Cada prueba se ejecuta individualmente con pausa para analizar resultados
- **Input personalizado**: Permite probar cualquier comando manualmente
- **Modo batch**: Ejecuta múltiples pruebas automáticamente
- **Integración con Valgrind**: Para detectar memory leaks
- **Output detallado**: Muestra la matriz de tokens generada para cada input

## Estructura del output

Para cada prueba verás:
```
========================================
TEST X: Descripción de la prueba
Input: "comando de prueba"
========================================
=== TOKEN MATRIX DEBUG ===
[0] String: |ls| -> Type: COMMAND_ROUTE
[1] String: |-la| -> Type: ARGUMENT
=== END TOKEN MATRIX ===
========================================
Press ENTER to continue...
```

## Consejos de uso

1. **Empezar con comandos simples**: Comienza con la categoría 1 para verificar el funcionamiento básico
2. **Revisar cada resultado**: Analiza si los tokens generados son correctos para cada input
3. **Probar casos edge**: Presta especial atención a los casos de error y situaciones límite
4. **Usar Valgrind regularmente**: Para asegurar que no hay memory leaks
5. **Probar inputs personalizados**: Usa la opción 9 del menú para probar casos específicos de tu interés

## Personalización

Puedes añadir más casos de prueba editando las arrays `tests[]` en cada función de `test_parser.c`. Cada caso de prueba tiene la estructura:

```c
{"input_command", "Descripción de la prueba"}
```

## Debugging

Si encuentras problemas:

1. Compila con flags de debug: `-g -fsanitize=address`
2. Usa Valgrind: `./run_tests.sh valgrind`
3. Agrega prints de debug en tu parser si es necesario
4. Testa casos simples primero, luego ve aumentando la complejidad

## Dependencias

- GCC compiler
- Libft compilada
- Make
- Valgrind (opcional, para detección de memory leaks)
- Bash (para el script run_tests.sh)
