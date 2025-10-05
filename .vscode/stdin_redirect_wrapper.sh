#!/bin/sh
# Wrapper ejecutado por gdb para redirigir stdin desde un archivo durante la depuración

if [ -n "$MINISHELL_STDIN_FILE" ] && [ -r "$MINISHELL_STDIN_FILE" ]; then
    exec "$@" < "$MINISHELL_STDIN_FILE"
else
    exec "$@"
fi
