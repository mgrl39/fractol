# Calculos de Julia

Este archivo documenta las funciones responsables de realizar los cálculos necesarios para la generación y renderización de fractales. Estas funciones gestionan aspectos como las escalas, los límites y el mapeo de píxeles a coordenadas del plano complejo.

---

## 1. julia_iterations

### Definición
```c
static void julia_iterations(t_render_vars *vars, t_data *data)
{
    double temp_z_re;

    vars->iterations = 0;
    while (vars->z_squared[COMPLEX_RE] + vars->z_squared[COMPLEX_IM] <= 4.0 &&
           vars->iterations < MAX_ITERATIONS)
    {
        temp_z_re = vars->z_squared[COMPLEX_RE];
        temp_z_re -= vars->z_squared[COMPLEX_IM];
        temp_z_re += data->c[COMPLEX_RE];
        vars->z[COMPLEX_IM] = 2.0 * vars->z[COMPLEX_RE] * vars->z[COMPLEX_IM] + data->c[COMPLEX_IM];
        vars->z[COMPLEX_RE] = temp_z_re;
        vars->z_squared[COMPLEX_RE] = vars->z[COMPLEX_RE] * vars->z[COMPLEX_RE];
        vars->z_squared[COMPLEX_IM] = vars->z[COMPLEX_IM] * vars->z[COMPLEX_IM];
        vars->iterations++;
    }
}
```

### ¿Qué hace esta función?

Esta función realiza las iteraciones necesarias para determinar si un punto del plano complejo pertenece al conjunto de Julia. Calcula repetidamente la fórmula iterativa de Julia:

```plaintext
z_n+1 = (z_n * z_n) + c
```

#### Parámetros:
- `vars`: Contiene las variables de renderizado, como las coordenadas del punto y el número de iteraciones.
- `data`: Contiene información del fractal, incluyendo la constante `c` utilizada para el cálculo.

---

### Detalles del Funcionamiento

#### 1. Condición de escape
```c
vars->z_squared[COMPLEX_RE] + vars->z_squared[COMPLEX_IM] <= 4.0
```

- El fractal considera que un punto "escapa" si la suma de los cuadrados de sus partes real e imaginaria es mayor que `4`.

Ejemplo: Si `z = 1 + 1i`, entonces:
```plaintext
|z|^2 = (1 * 1) + (1 * 1) = 2
```

---

#### 2. Actualización del valor de `z`
```c
temp_z_re = vars->z_squared[COMPLEX_RE] - vars->z_squared[COMPLEX_IM] + data->c[COMPLEX_RE];
vars->z[COMPLEX_IM] = 2.0 * vars->z[COMPLEX_RE] * vars->z[COMPLEX_IM] + data->c[COMPLEX_IM];
vars->z[COMPLEX_RE] = temp_z_re;
```

La fórmula completa en código sería:
```plaintext
z_real = (z_real^2) - (z_imag^2) + c_real
z_imag = 2 * z_real * z_imag + c_imag
```

---

### Ejemplo de Iteraciones

Supongamos:
- `z = 0 + 0i`
- `c = 0.285 - 0.01i`
- Máximo de iteraciones: 10

**Iteraciones:**
1. `z_1 = (0 * 0 - 0 * 0 + 0.285) + (2 * 0 * 0 - 0.01)i = 0.285 - 0.01i`
2. Repetir con `z_1`.

## 2. render_julia_row

### Definición
```c
static void render_julia_row(t_render_vars *vars, t_data *data, int y)
{
    int x;

    x = 0;
    while (x < WIDTH)
    {
        vars->c_re[0] = vars->start[COMPLEX_RE] + x * vars->scale[SCALE_X];
        vars->z[COMPLEX_RE] = vars->c_re[0];
        vars->z[COMPLEX_IM] = vars->c_im;
        vars->z_squared[COMPLEX_RE] = vars->z[COMPLEX_RE] * vars->z[COMPLEX_RE];
        vars->z_squared[COMPLEX_IM] = vars->z[COMPLEX_IM] * vars->z[COMPLEX_IM];
        julia_iterations(vars, data);
        vars->row = vars->pixels + y * WIDTH + x;
        *vars->row = calculate_color(vars->iterations);
        x++;
    }
}
```

### ¿Qué hace esta función?

La función `render_julia_row` renderiza una fila completa del fractal de Julia. Realiza las siguientes acciones para cada píxel en la fila:

1. Calcula el número complejo inicial `z` para el píxel actual en función de las coordenadas del píxel y la escala.
2. Ejecuta el algoritmo de iteraciones de Julia para determinar el número de iteraciones necesarias para que el punto escape.
3. Usa el número de iteraciones para determinar el color del píxel mediante la función `calculate_color`.
4. Guarda el color calculado en el buffer de píxeles.

### Parámetros

- `t_render_vars *vars`: Puntero a la estructura que contiene variables utilizadas en el proceso de renderizado, como las escalas, las coordenadas iniciales, y el buffer de píxeles.
- `t_data *data`: Puntero a la estructura que contiene los datos del fractal, como la constante del conjunto de Julia y el nivel de zoom.
- `int y`: Índice de la fila (coordenada `y`) que se está renderizando.

---

### Detalles del funcionamiento

#### 1. Cálculo de la coordenada real inicial del píxel
```c
vars->c_re[0] = vars->start[COMPLEX_RE] + x * vars->scale[SCALE_X];
```
- Convierte la posición del píxel en la pantalla (`x`) a una coordenada real en el plano complejo.
- La fórmula es:
  ```
  c_re = start[COMPLEX_RE] + x * scale[SCALE_X]
  ```

#### 2. Inicialización del número complejo `z`
```c
vars->z[COMPLEX_RE] = vars->c_re[0];
vars->z[COMPLEX_IM] = vars->c_im;
```
- Asigna la parte real de `z` al valor calculado en el paso anterior.
- Asigna la parte imaginaria de `z` a `vars->c_im`, que corresponde a la fila actual.

#### 3. Ejecución del algoritmo de iteraciones de Julia
```c
julia_iterations(vars, data);
```
- Llama a la función `julia_iterations` para determinar cuántas iteraciones son necesarias para que el punto escape.

#### 4. Cálculo del color del píxel
```c
*vars->row = calculate_color(vars->iterations);
```
- Usa el número de iteraciones calculado para asignar un color al píxel.
- El resultado se almacena en el buffer de píxeles (`vars->pixels`).

---

### Ejemplo Práctico

#### Supongamos:
- Coordenada del píxel: `(x, y) = (100, 50)`
- Inicio del plano complejo: `start[COMPLEX_RE] = -2.0`
- Escala: `scale[SCALE_X] = 0.005`
- Resultado:
  ```plaintext
  c_re = -2.0 + 100 * 0.005 = -1.5
  ```

## 3. render_julia

### Definición
```c
void render_julia(t_data *data)
{
    t_render_vars vars;
    int y;

    calculate_scales_and_limits(&vars, data);
    y = 0;
    while (y < HEIGHT)
    {
        vars.c_im = vars.start[COMPLEX_IM] + y * vars.scale[SCALE_Y];
        render_julia_row(&vars, data, y++);
    }
}
```

### ¿Qué hace esta función?

La función `render_julia` renderiza el fractal completo del conjunto de Julia. Procesa fila por fila y delega el cálculo de cada fila a la función `render_julia_row`.

### Parámetros

- `t_data *data`: Puntero a la estructura que contiene los datos del fractal, como el nivel de zoom, el desplazamiento, y la constante del conjunto de Julia.

---

### Detalles del funcionamiento

#### 1. Configuración inicial
```c
calculate_scales_and_limits(&vars, data);
```
- Calcula las escalas y los límites del plano complejo que se usarán para renderizar el fractal.

#### 2. Iteración sobre cada fila
```c
while (y < HEIGHT)
{
    vars.c_im = vars.start[COMPLEX_IM] + y * vars.scale[SCALE_Y];
    render_julia_row(&vars, data, y++);
}
```
- Recorre cada fila (`y`) de la imagen.
- Para cada fila:
  1. Calcula la coordenada imaginaria inicial (`c_im`) de la fila.
     ```plaintext
     c_im = start[COMPLEX_IM] + y * scale[SCALE_Y]
     ```
  2. Llama a `render_julia_row` para renderizar todos los píxeles de la fila.

---

### Ejemplo Práctico

#### Supongamos:
- Altura de la ventana: `HEIGHT = 800`
- Inicio del plano complejo: `start[COMPLEX_IM] = -2.0`
- Escala: `scale[SCALE_Y] = 0.005`

#### Resultado para la fila `y = 100`:
1. Coordenada imaginaria inicial:
   ```plaintext
   c_im = -2.0 + 100 * 0.005 = -1.5
   ```

2. La fila completa se renderiza llamando a `render_julia_row`.

---

### Importancia del Proceso Completo

1. **Estructura Modular:**
   - Separar la renderización en filas facilita la comprensión y el mantenimiento del código.

2. **Reutilización de Cálculos:**
   - Los cálculos iniciales de escala y límites optimizan el proceso de renderizado.

3. **Flexibilidad:**
   - La separación por filas permite implementar técnicas como renderizado paralelo para mejorar el rendimiento.

4. **Conexión entre Coordenadas:**
   - Traduce las coordenadas del plano complejo a píxeles en la ventana gráfica de manera precisa.

