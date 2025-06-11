# Percolation Simulation Project

## Descripción

Este proyecto implementa una simulación de percolación en 2D utilizando el algoritmo de Hoshen-Kopelman para identificar clusters conectados. El objetivo es estudiar el fenómeno de percolación y calcular probabilidades.

## Estructura del Proyecto
```
MiddleProyect-HPC-2025/
├── src/
│   ├── main.cpp             # Programa principal con modos de ejecución
│   ├── percolation.cpp      # Implementación del algoritmo Hoshen-Kopelman
│   ├── statistic.cpp        # Funciones de análisis estadístico
│   ├── percolation.h        # Declaraciones de funciones y estructuras
│   └── test.cpp             # Suite de pruebas unitarias
├── data/
│   ├── matrix_data.txt      # Datos de matriz individual (generado)
│   ├── study_L*.txt         # Resultados por tamaño de sistema (generado)
│   └── profiling-report.txt # Reporte de rendimiento (generado)
├── Makefile                 # Sistema de construcción
└── README.md                # Este archivo
```

## Compilación

### Requisitos
- Compilador C++ compatible con C++17 (g++)
- Sistema Unix/Linux

### Compilar el proyecto
```bash
make
```

### Compilar versión de pruebas
```bash
make test.x
```

## Uso

### Simulación Individual

Ejecutar una simulación con tamaño de red L y probabilidad p:

```bash
./percolation.x <L> <p>
```

**Ejemplo:**
```bash
./percolation.x 50 0.59
```

**Salida esperada:**
```
Running single percolation test: L = 50, p = 0.59
Results:
  System percolates: Yes
  Total clusters: 127
  Largest cluster size: 1456
  Mean cluster size: 19.67
  Standard deviation: 120.45
  Computation time: 2341 µs
  Percolating cluster detected!
Matrix data saved to data/matrix_data.txt
```

## Targets del Makefile

- `make` o `make all` - Compila el programa principal
- `make test` - Compila y ejecuta las pruebas unitarias
- `make test.x` - Solo compila las pruebas
- `make clean` - Limpia archivos de compilación (.o, .x)
- `make clean-all` - Limpia archivos de compilación y datos generados
- `make run-single` - Ejecuta ejemplo rápido (L=20, p=0.5)
- `make run-study` - Ejecuta estudio completo

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

### Análisis Estadístico

El programa calcula múltiples métricas estadísticas:

- **Probabilidad de percolación**: P(p,L) = número de sistemas percolantes / número total de pruebas
- **Tamaño promedio de clusters**: Media de tamaños de clusters percolantes
- **Desviación estándar**: Variabilidad en los tamaños de clusters
- **Cluster más grande**: Tamaño del cluster de mayor tamaño

## Archivos de Salida

### Simulación Individual
- `data/matrix_data.txt`: Datos de la matriz en formato (i, j, cluster_id)

### Estudio Completo
- `data/study_L<N>.txt`: Resultados para sistema de tamaño N
  - Columnas: p, Probabilidad_Percolación, Tamaño_Promedio_Cluster, Tiempo_ms
- `data/profiling-report.txt`: Reporte completo de rendimiento
  - Columnas: L, p, Pruebas, Tiempo_ms, Prob_Percolación, Tamaño_Promedio, Desv_Estándar

## Parámetros del Estudio

### Tamaños de Sistema
- L ∈ {32, 64, 128, 256, 512}

### Valores de Probabilidad
- Rango principal: p = 0.00 a 1.00 (intervalo 0.05)
- Valores adicionales cerca del punto crítico: {0.52, 0.54, 0.56, 0.58, 0.61, 0.62, 0.63, 0.67, 0.68}

## Optimizaciones Implementadas
- **Union-Find con compresión de caminos**: Optimiza la fusión de clusters
- **Union by rank**: Mantiene árboles balanceados en Union-Find
- **Generador de números aleatorios eficiente**: std::mt19937 con semilla basada en hardware
- **Compilación optimizada**: Flags -O3 para máximo rendimiento
- **Sanitizers**: Detección de errores de memoria y comportamiento indefinido

## Autor

...
