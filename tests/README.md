# Tests Directory

Este directorio contiene todos los archivos relacionados con testing del proyecto Minishell.

## Estructura

```
tests/
├── README.md           # Este archivo
├── Makefile.test       # Makefile con sistema de dependencias mejorado
├── run_tests.sh        # Script para ejecutar todos los tests
├── fallos.txt          # Log de fallos conocidos
├── TEST_README.md      # Documentación adicional de tests
├── obj/                # Archivos objeto (generado automáticamente)
├── parser/             # Tests específicos del parser
│   └── test_parser.c   # Tests del parser
└── utils/              # Utilidades para testing
    └── debug_functions.c # Funciones de debug
```

## Uso

### Compilar tests
```bash
make -f Makefile.test
```

El sistema de compilación ahora:
- ✅ **Detecta cambios automáticamente**: Solo recompila archivos modificados
- ✅ **Gestión de dependencias**: Detecta cambios en headers automáticamente
- ✅ **Compilación incremental**: Más rápido en builds subsecuentes
- ✅ **Archivos objeto organizados**: En directorio `obj/` separado

### Ejecutar tests
```bash
./run_tests.sh
```

### Limpiar archivos compilados
```bash
make -f Makefile.test clean      # Solo archivos objeto
make -f Makefile.test fclean     # Todo incluyendo ejecutable
```

### Tests específicos del parser
```bash
cd parser/
# Compilar y ejecutar test_parser
```

## Archivos

- **Makefile.test**: Contiene las reglas de compilación para los tests
- **run_tests.sh**: Script automatizado para ejecutar todos los tests
- **fallos.txt**: Registro de fallos conocidos y casos edge
- **parser/test_parser.c**: Tests unitarios para las funciones del parser
- **utils/debug_functions.c**: Funciones auxiliares para debugging durante los tests
