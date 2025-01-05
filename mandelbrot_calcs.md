# Calculos de Mandelbrot

El archivo `mandelbrot.c` contiene la lógica necesaria para renderizar el conjunto de Mandelbrot en el proyecto Fractol. Este archivo incluye funciones para realizar iteraciones en puntos del plano complejo, optimizar las condiciones de escape y mapear los resultados a colores en los píxeles.

## 1. compute_next_iteration

### Definición
```c
static void compute_next_iteration(t_render_vars *vars, int i)
{
    double temp_z_re;

    temp_z_re = vars->z_squared[COMPLEX_RE] - vars->z_squared[COMPLEX_IM];
    temp_z_re += vars->c_re[i];
    vars->z[COMPLEX_IM] = (2.0 * vars->z[COMPLEX_RE] * vars->z[COMPLEX_IM]);
    vars->z[COMPLEX_IM] += vars->c_im;
    vars->z[COMPLEX_RE] = temp_z_re;
    vars->z_squared[COMPLEX_RE] = vars->z[COMPLEX_RE] * vars->z[COMPLEX_RE];
    vars->z_squared[COMPLEX_IM] = vars->z[COMPLEX_IM] * vars->z[COMPLEX_IM];
}
```

### ¿Qué hace esta función?

Calcula la siguiente iteración de `z` usando la fórmula iterativa del conjunto de Mandelbrot:

```
z_n+1 = z_n^2 + c
```

**Explicación:**
- Usa los valores actuales de `z` (parte real e imaginaria) y la constante `c` (coordenadas del píxel en el plano complejo).
- Actualiza los valores de `z` y los cuadrados de sus componentes para las próximas iteraciones.

### Parámetros
- `t_render_vars *vars`: Contiene las variables necesarias para los cálculos, incluyendo `z`, `c`, y sus cuadrados.
- `int i`: Índice del punto en el conjunto de datos.

### Ejemplo Práctico

Supongamos:
- `z = 0 + 0i`
- `c = -0.75 + 0.1i`

**Iteraciones:**
1. 
```
z_1_real = 0^2 - 0^2 + (-0.75) = -0.75
z_1_imag = 2 * 0 * 0 + 0.1 = 0.1
```
2. 
```
z_2_real = (-0.75)^2 - (0.1)^2 + (-0.75) = -0.1975
z_2_imag = 2 * (-0.75) * 0.1 + 0.1 = -0.05
```

---

## 2. mandelbrot_iterations

### Definición
```c
static void mandelbrot_iterations(t_render_vars *vars, int i)
{
    double current_magnitude_squared;
    double escape_radius_squared;

    escape_radius_squared = 4.0;
    vars->z[COMPLEX_RE] = 0.0;
    vars->z[COMPLEX_IM] = 0.0;
    vars->z_squared[COMPLEX_RE] = 0;
    vars->z_squared[COMPLEX_IM] = 0;
    vars->iterations = 0;
    while (1)
    {
        current_magnitude_squared = vars->z_squared[COMPLEX_RE];
        current_magnitude_squared += vars->z_squared[COMPLEX_IM];
        if (vars->iterations >= MAX_ITERATIONS)
            break ;
        if (current_magnitude_squared > escape_radius_squared)
            break ;
        compute_next_iteration(vars, i);
        vars->iterations++;
    }
}
```

### ¿Qué hace esta función?

Determina si un punto pertenece al conjunto de Mandelbrot. Aplica iterativamente la fórmula hasta que:
1. 
```
|z|^2 > 4
```
   (El punto escapa del conjunto).
2. Se alcanza el máximo de iteraciones (`MAX_ITERATIONS`), lo que indica que el punto es parte del conjunto o está muy cercano.

### Parámetros
- `t_render_vars *vars`: Variables necesarias para los cálculos, como `z`, `c`, y el número de iteraciones.
- `int i`: Índice del punto actual.

### Ejemplo Práctico

Para `c = -0.75 + 0.1i`:
1. 
```
z_0 = 0 + 0i
|z|^2 = 0
```
2. 
```
z_1 = -0.75 + 0.1i
|z|^2 = 0.5725
```
3. 
```
z_2 = -0.1975 - 0.05i
|z|^2 = 0.0413
```

---

## 3. mandelbrot_escape_check

### Definición
```c
static int	mandelbrot_escape_check(t_render_vars *vars, int i, t_data *data)
{
	int		max_color;
	double	dist_sq;
	double	esc_chk;
	double	bound_condition;

	max_color = calculate_color(MAX_ITERATIONS);
	vars->c_re_centered = vars->c_re[i] - 0.25;
	dist_sq = vars->c_re_centered * vars->c_re_centered;
	dist_sq += vars->c_im * vars->c_im;
	esc_chk = dist_sq * (dist_sq + vars->c_re_centered);
	if ((data->zoom > 1.0) && (esc_chk < 0.25 * vars->c_im * vars->c_im))
		return (vars->row[i] = max_color, 1);
	bound_condition = (vars->c_re[i] + 1) * (vars->c_re[i] + 1);
	bound_condition += vars->c_im * vars->c_im;
	if (bound_condition < 0.0625)
		return (vars->row[i] = max_color, 1);
	return (0);
}
```

### ¿Qué hace esta función?

Optimiza la detección de puntos que están garantizados como parte del conjunto de Mandelbrot, evitando realizar todas las iteraciones.

**Explicación:**
- Comprueba si el punto está en regiones conocidas del conjunto usando condiciones geométricas predefinidas.

### Parámetros
- `t_render_vars *vars`: Variables de cálculo.
- `int i`: Índice del punto.
- `t_data *data`: Información del fractal, como el nivel de zoom.

---

## 4. render_mandelbrot_row

### Definición
```c
static void render_mandelbrot_row(t_render_vars *vars, t_data *data, int y)
{
    int x, i;

    x = 0;
    while (x < WIDTH)
    {
        vars->row = vars->pixels + (y * WIDTH + x);
        vars->c_re[0] = vars->start[COMPLEX_RE] + x * vars->scale[SCALE_X];
        vars->c_re[1] = vars->start[COMPLEX_RE] + (x + 1) * vars->scale[SCALE_X];
        i = 0;
        while (i < 2)
        {
            if (mandelbrot_escape_check(vars, i, data))
            {
                i++;
                continue ;
            }
            mandelbrot_iterations(vars, i);
            vars->row[i++] = calculate_color(vars->iterations);
        }
        x += 2;
    }
}
```

### ¿Qué hace esta función?

Renderiza una fila completa del fractal:
1. Calcula los valores de `c` para cada píxel.
2. Aplica condiciones de escape rápidas.
3. Realiza iteraciones para determinar el color del píxel.

### Parámetros
- `t_render_vars *vars`: Variables de cálculo.
- `t_data *data`: Información del fractal.
- `int y`: Índice de la fila.

---

## 5. render_mandelbrot

### Definición
```c
void	render_mandelbrot(t_data *data)
{
	t_render_vars	vars;
	double			*precomputed_c_re;
	double			*precomputed_c_im;
	int				y;

	calculate_scales_and_limits(&vars, data);
	if (!precompute_coords(&precomputed_c_re, &precomputed_c_im, &vars))
		return ;
	y = 0;
	while (y < HEIGHT)
	{
		vars.c_im = precomputed_c_im[y];
		render_mandelbrot_row(&vars, data, y++);
	}
	free(precomputed_c_re);
	free(precomputed_c_im);
}
```

### ¿Qué hace esta función?

Renderiza el fractal completo fila por fila. Precomputa las coordenadas de los píxeles para optimizar el cálculo durante el proceso de renderizado.

### Parámetros
- `t_data *data`: Información del fractal.

