# Percolation Simulation Project

## Descripción

Este proyecto implementa una simulación de percolación en 2D utilizando el algoritmo de Hoshen-Kopelman para identificar clusters conectados. El objetivo es estudiar el fenómeno de percolación de sitios en una red cuadrada y calcular probabilidades críticas.

## Estructura del Proyecto

```
percolation_project/
├── src/
│   ├── main.cpp           # Programa principal
│   ├── percolation.cpp    # Funciones de percolación y Hoshen-Kopelman
│   └── statistic.cpp     # Funciones estadísticas
│   └── percolation.h      # Declaraciones de funciones
├── data/
│   └── ...
├── scripts/
│   └── plot_results.gnu   # Script de Gnuplot para visualización
├── docs/
│   └── report.pdf         # Documentación del proyecto
├── Makefile               # Sistema de construcción
└── README.md              # Este archivo
```

## Compilación

Para compilar el proyecto:

```bash
make
```

## Uso

### Simulación Individual

Ejecutar una simulación con tamaño de red L y probabilidad p:

```bash
./percolation <L> <p>
```

Ejemplo:
```bash
./percolation 20 0.6
```

<!-- ## Targets del Makefile

- `make all` - Compila el proyecto
- `make test` - Ejecuta pruebas básicas
- `make plot` - Genera gráficos con gnuplot
- `make clean` - Limpia archivos de compilación -->

## Algoritmo

### Hoshen-Kopelman

El algoritmo de Hoshen-Kopelman se utiliza para identificar y etiquetar clusters conectados:

1. Se recorre la matriz de izquierda a derecha, de arriba a abajo
2. Para cada sitio ocupado, se verifica la conectividad con vecinos ya visitados
3. Se asignan etiquetas únicas a cada cluster
4. Se fusionan clusters cuando se detectan conexiones

### Detección de Percolación

Un sistema percola si existe al menos un cluster que conecta bordes opuestos:
- **Percolación horizontal**: Cluster que conecta columna izquierda con derecha
- **Percolación vertical**: Cluster que conecta fila superior con inferior

## Visualización

Los resultados se pueden visualizar usando:

```bash
make plot
```

Esto genera:
...

## Parámetros
...

## Archivos de Salida
...


## Ejemplo de Uso Completo

```bash
# Compilar
make

# Simulación individual
./percolation 50 0.59

...

# Ejecutar pruebas
make test
```

## Notas Técnicas

- El proyecto usa C++17 con optimización -O3
- Se incluye manejo de memoria automático con std::vector
- Generador de números aleatorios ...
- Compatible con sistemas Unix/Linux

## Dependencias

- Compilador C++ compatible con C++17 (g++)
- Gnuplot (opcional, para visualización)
- Make

## Autor

...
