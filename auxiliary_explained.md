# Funciones Auxiliares

Este archivo documenta las funciones auxiliares utilizadas en el proyecto. Estas funciones son clave para manejar tareas como salida de texto, manipulación de cadenas y conversión de datos.

## 1. ft_strcmp
### Definición
```c
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (s1[i] - s2[i]);
}
```

### ¿Qué hace esta función?
`ft_strcmp` compara dos cadenas de texto (`s1` y `s2`) carácter por carácter. Si ambas cadenas son idénticas, devuelve `0`. Si no, devuelve la diferencia numérica entre los valores ASCII del primer par de caracteres diferentes.

### Parámetros
- `const char *s1`: Puntero a la primera cadena de texto que se desea comparar.
- `const char *s2`: Puntero a la segunda cadena de texto que se desea comparar.

### Retorno
- Devuelve `0` si las cadenas son iguales.
- Devuelve un valor positivo si `s1` es mayor que `s2` (el primer carácter diferente en `s1` tiene un valor ASCII mayor que en `s2`).
- Devuelve un valor negativo si `s1` es menor que `s2` (el primer carácter diferente en `s1` tiene un valor ASCII menor que en `s2`).

### Detalles del funcionamiento
1. Iteración carácter por carácter:
   - Compara los caracteres correspondientes de `s1` y `s2` hasta que encuentra una diferencia o llega al final de una de las cadenas.
2. Verificación de igualdad:
   - Si los caracteres son iguales, sigue comparando.
   - Si encuentra un carácter diferente, calcula y devuelve la diferencia entre sus valores ASCII.
3. Cadena más corta:
   - Si una cadena termina antes que la otra, la función considera que la más corta es "menor".

### Ejemplo de uso
**Es el encargado de detectar si han indicado `mandelbrot` o `julia`**

### ¿Por qué es útil?
Esta función es esencial para la comparación de cadenas en algoritmos como la ordenación de palabras alfabéticamente, búsqueda en bases de datos, o cualquier otra operación que requiera conocer el orden relativo entre dos cadenas de texto.

## 2. fr_putstr_fd
### Definición
```c
int	fr_putstr_fd(char *s, int fd)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i])
		count += write(fd, &s[i++], 1);
	return (count);
}
```

### ¿Qué hace esta función?
`fr_putstr_fd` escribe una cadena de texto (`s`) en un descriptor de archivo (`fd`). Es similar a `puts` pero con la capacidad de escribir en cualquier descriptor de archivo, como salida estándar (1) o error estándar (2).

### Parámetros
- `char *s`: Puntero a la cadena de texto que se desea escribir.
- `int fd`: Descriptor de archivo donde se escribe la cadena:
  - `1` para salida estándar (`stdout`).
  - `2` para salida de error (`stderr`).

### Retorno
Devuelve el número total de caracteres escritos. Si la cadena es `NULL`, devuelve `0`.

### Detalles del funcionamiento
1. Validación inicial:
   - Si la cadena `s` es `NULL`, la función retorna `0` inmediatamente.
2. Iteración y escritura:
   - Recorre la cadena carácter por carácter usando un índice (`i`).
   - Escribe cada carácter en el descriptor de archivo usando `write`.
   - Incrementa un contador (`count`) con el número de bytes escritos.
3. Devolución:
   - Retorna el valor acumulado en `count`, que representa el total de caracteres escritos.

### Ejemplo de uso
**Es el encargado de imprimir los errores cuando no indican los parametros correctamente.**

### ¿Por qué es útil?
Esta función simplifica la escritura en descriptores de archivo, permitiendo imprimir mensajes personalizados en la salida estándar o en la salida de error, sin necesidad de gestionar directamente `write`.

## 3. is_valid_number
### Definición
```c
static int	is_valid_number(const char *str)
{
	int	i;
	int	valid_status[2];

	i = 0;
	valid_status[HAS_DIGIT] = 0;
	valid_status[HAS_POINT] = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		valid_status[HAS_DIGIT] = 1;
		i++;
	}
	if (str[i] == '.')
	{
		valid_status[HAS_POINT] = 1;
		i++;
	}
	if (valid_status[HAS_POINT] && (str[i] < '0' || str[i] > '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (valid_status[HAS_DIGIT] && str[i] == '\0');
}
```

### ¿Qué hace esta función?
`is_valid_number` verifica si una cadena de texto representa un número válido. Esto incluye números enteros y de punto flotante con signo opcional.

### Parámetros
- `const char *str`: Puntero a la cadena de texto que se desea validar.

### Retorno
- Devuelve `1` si la cadena es un número válido.
- Devuelve `0` si la cadena no es válida como número.

### Detalles del funcionamiento
1. Ignora los espacios iniciales y caracteres de control.
2. Permite un signo (`+` o `-`) al inicio.
3. Verifica que la cadena contenga al menos un dígito antes o después de un punto decimal (`.`).
4. Si hay un punto decimal, asegura que le sigan dígitos.
5. Comprueba que no haya caracteres adicionales después del número.

### Ejemplo de uso
**Es el encargado de validar que las coordenadas pasadas para `julia` sean números correctos.**

### ¿Por qué es útil?
Esta función asegura que los parámetros numéricos proporcionados por el usuario sean válidos, evitando errores en cálculos posteriores.

## 4. calculate_color
### Definición
```c
int	calculate_color(int iterations)
{
	double	t;
	int		base_gray;
	t_color	color;

	t = (double)iterations / MAX_ITERATIONS;
	base_gray = (30 + 190 * (t * (1 - 0.2 * t)));
	color.r = base_gray - (5 * (1 - t) * t * t);
	color.g = base_gray - (10 * (1 - t) * (1 - t));
	color.b = base_gray - (15 * (1 - t) * t);
	return ((0xFF << 24) | (color.r << 16) | (color.g << 8) | color.b);
}
```

### ¿Qué hace esta función?
`calculate_color` genera un color basado en el número de iteraciones realizadas para un píxel en el fractal. Produce un gradiente suave para mejorar la apariencia visual del fractal.

### Parámetros
- `int iterations`: Número de iteraciones para el píxel actual.

### Retorno
- Devuelve el color calculado en formato ARGB (Alpha-Red-Green-Blue).

### Detalles del funcionamiento
1. **Cálculo del factor `t`:**
   - Normaliza el número de iteraciones (`iterations`) al rango `[0, 1]` dividiéndolo por el máximo permitido (`MAX_ITERATIONS`).
2. **Base gris:**
   - Calcula una base de gris a partir de `t`, ajustando el brillo para crear un efecto de gradiente.
    ```c
    base_gray = (30 + 190 * (t * (1 - 0.2 * t)));
    ```
    `t` se ajusta para crear una curva suave mediante la fórmula: `t * ( 1 - 0.2 * t)`. Esto gnera una transición fluida en el gradiente.
3. **Componentes RGB:**
   - Ajusta cada componente (`r`, `g`, `b`) para añadir variaciones de color dependiendo del nivel de iteración.
   ```c
    color.r = base_gray - (5 * (1 - t) * t * t);
    color.g = base_gray - (10 * (1 - t) * (1 - t));
    color.b = base_gray - (15 * (1 - t) * t);
    ```
    - Cada componente tiene una fórmula ligeramente diferente para generar colors distintivos y visualmente agradables:
        - El rojo depende más de t^3 (potencia alta).
        - El azul se ajusta con (1 - t)^2 (mas dominante en el rango medio).
        - El azul usa una combinación de (1 - t) y t para un efeco más suave.

4. **Formato ARGB:**
   - Combina los componentes en un entero de 32 bits con un canal Alpha completamente opaco (`0xFF`).
   ```c
   return (0xFF << 24 | (color.r << 16) | (color.g << 8) | color.b);
   ```
   - La función empaqueta los componentes en un entero en formato ARGB (Alpha, Red, Green, Blue):
    - `0xFF << 24` -> Fija el canal alfa a 255 (completamente opaco).
    - `(color.r << 16)` -> Inserta el componente rojo en los bits altos.
    - `(color.g << 8)` -> Inserta el componente verde.
    - `color.b` -> Inserta el componente azul.

### Ejemplo de uso
**Es el encargado de calcular el color de cada píxel en función de su número de iteraciones.**

### ¿Por qué es útil?
Esta función mejora significativamente la representación visual del fractal, permitiendo distinguir las diferentes áreas según su comportamiento iterativo y creando una experiencia más atractiva para el usuario.

## 5. calculate_scales_and_limits

### Definición
```c
void calculate_scales_and_limits(t_render_vars *vars, t_data *data)
{
    vars->scale[SCALE_X] = 4.0 / (WIDTH * data->zoom);
    vars->scale[SCALE_Y] = 4.0 / (HEIGHT * data->zoom);
    vars->start[COMPLEX_RE] = -2.0 / data->zoom + data->offset[OFFSET_X];
    vars->start[COMPLEX_IM] = -2.0 / data->zoom + data->offset[OFFSET_Y];
    vars->pixels = (uint32_t *)data->img->pixels;
}
```

### ¿Qué hace esta función?

La función `calculate_scales_and_limits` calcula las escalas y límites del plano complejo que se usarán para renderizar el fractal en la ventana gráfica. Estos valores permiten traducir cada píxel de la pantalla a un número complejo, lo que es esencial para los cálculos iterativos del fractal.

### Parámetros

- `t_render_vars *vars`: Estructura donde se almacenan las escalas, los límites iniciales del plano complejo, y un puntero al buffer de píxeles.
- `t_data *data`: Contiene la información del fractal, como el nivel de zoom y el desplazamiento actual.

---

### Detalles del funcionamiento

#### 1. Cálculo de las escalas
```c
vars->scale[SCALE_X] = 4.0 / (WIDTH * data->zoom);
vars->scale[SCALE_Y] = 4.0 / (HEIGHT * data->zoom);
```

- **¿Por qué 4.0?**
  - El plano complejo inicial tiene un rango estándar de `[-2.0, +2.0]` en ambos ejes (real e imaginario). Este rango totaliza una longitud de `4.0`.

- **¿Qué hace la escala?** - La escala indica cuánto representa cada píxel en el plano complejo. Por ejemplo: - Con `zoom = 1.0`, cada píxel representa `4.0 / WIDTH`.
    - Con `zoom = 2.0`, la escala es más pequeña, permitiendo un mayor detalle al acercarse.

---

#### 2. Cálculo de los límites iniciales
```c
vars->start[COMPLEX_RE] = -2.0 / data->zoom + data->offset[OFFSET_X];
vars->start[COMPLEX_IM] = -2.0 / data->zoom + data->offset[OFFSET_Y];
```

- **¿Por qué -2.0?**
  - La esquina superior izquierda del rango inicial del fractal comienza en `(-2.0, -2.0)` en el plano complejo. Este punto corresponde al primer píxel de la ventana gráfica.

- **Zoom y desplazamiento:**
  - El `zoom` ajusta el tamaño del rango visible del fractal.
  - El desplazamiento (`data->offset`) permite mover el rango visible del fractal a diferentes partes del plano complejo.

---

#### 3. Asignación del buffer de píxeles
```c
vars->pixels = (uint32_t *)data->img->pixels;
```

- **¿Qué es `data->img->pixels`?**
  - Es un puntero al área de memoria donde se almacenan los colores de cada píxel que se renderizarán en la ventana gráfica.

- **¿Por qué se castea a `uint32_t`?**
  - Los píxeles están representados como enteros de 32 bits (ARGB: Alpha, Red, Green, Blue). Castearlos a `uint32_t` facilita modificar el color de cada píxel de manera eficiente.

---

### Ejemplo práctico

#### Supongamos:
- **Ventana gráfica:** `WIDTH = 800`, `HEIGHT = 800`.
- **Zoom inicial:** `1.0`.
- **Desplazamiento inicial:** `[OFFSET_X, OFFSET_Y] = [0.0, 0.0]`.

#### Resultado:
1. **Escalas:**
   ```plaintext
   scale[SCALE_X] = 4.0 / 800 = 0.005
   scale[SCALE_Y] = 4.0 / 800 = 0.005
   ```

2. **Límites iniciales:**
   ```plaintext
   start[COMPLEX_RE] = -2.0 + 0.0 = -2.0
   start[COMPLEX_IM] = -2.0 + 0.0 = -2.0
   ```

3. **Buffer de píxeles:**
   - `vars->pixels` apunta al inicio del buffer de memoria donde se almacenan los colores de los píxeles.

---

### Importancia de esta función

1. **Traducción entre píxeles y el plano complejo:**
   - Cada píxel de la pantalla se corresponde con un número complejo en el plano. Esta función establece esa correspondencia de manera precisa.

2. **Adaptabilidad al zoom y desplazamiento:**
   - Permite acercarse o alejarse del fractal ajustando las escalas, y desplazarse por diferentes partes del fractal modificando los límites.

3. **Eficiencia:**
   - Precalcular las escalas y los límites evita realizar estos cálculos para cada píxel, mejorando el rendimiento del renderizado.

4. **¿Por qué es crucial?**
   - Sin estas escalas y límites, sería imposible generar el fractal correctamente. Los fractales son gráficos basados en números complejos, y esta función conecta el mundo "físico" de los píxeles con el mundo "matemático" del plano complejo.

