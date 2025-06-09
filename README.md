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
├── include/
│   └── percolation.h      # Declaraciones de funciones
├── data/
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
make all
```

O simplemente:

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

### Cálculo de Probabilidad de Percolación

```bash
./percolation <L> <p> prob
```

### Estudio Completo de Probabilidades

```bash
./percolation <L> <p> study
```

## Targets del Makefile

- `make all` - Compila el proyecto
- `make run` - Ejecuta una simulación ejemplo (L=20, p=0.6)
- `make prob` - Calcula probabilidad de percolación
- `make study` - Ejecuta estudio completo de probabilidades
- `make test` - Ejecuta pruebas básicas
- `make plot` - Genera gráficos con gnuplot
- `make clean` - Limpia archivos de compilación
- `make help` - Muestra ayuda

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

## Análisis Estadístico

El proyecto calcula:

- **Probabilidad de percolación**: P(p,L) en función de p y L
- **Tamaño promedio de clusters percolantes**: s(p,L)
- **Desviación estándar** de los tamaños de clusters

## Visualización

Los resultados se pueden visualizar usando:

```bash
make plot
```

Esto genera:
- Gráfico de probabilidad de percolación vs probabilidad de sitio
- Visualización de la matriz de clusters

## Parámetros Recomendados

Para el estudio de percolación:
- **L**: {32, 64, 128, 256, 512}
- **p**: [0.0, 1.0] con pasos de 0.05
- **Ensayos**: Mínimo 10 por configuración para estadísticas confiables

## Archivos de Salida

- `data/matrix_data.txt` - Datos de la matriz para visualización
- `data/probability_study.txt` - Resultados del estudio de probabilidades
- `data/percolation_plot.png` - Gráfico de probabilidades
- `data/matrix_plot.png` - Visualización de la matriz

## Ejemplo de Uso Completo

```bash
# Compilar
make

# Simulación individual
./percolation 50 0.59

# Estudio completo
make study

# Generar gráficos
make plot

# Ejecutar pruebas
make test
```

## Notas Técnicas

- El proyecto usa C++17 con optimización -O2
- Se incluye manejo de memoria automático con std::vector
- Generador de números aleatorios Mersenne Twister
- Compatible con sistemas Unix/Linux

## Dependencias

- Compilador C++ compatible con C++17 (g++, clang++)
- Gnuplot (opcional, para visualización)
- Make

## Autor

Proyecto desarrollado para la clase de IntroSciHPC - Simulación de Percolación 2D