# Main Explained
Este archivo explica el main paso a paso. 
## 1. main: punto de entrada.
```c
int main(int argc, char *argv[])
```
El main es el **punto de entrada del programa**, es decir, el inicio. Los dos argumentos que toma son `argc` y `argv`.
- `argc` indica el número de argumentos pasados por línea de comandos.
- `argv` es el array de cadenas que contiene los argumentos.

Cuando escribimos en la terminal:
```c
./fractol mandelbrot
```
- **argc** vale **2**, ya que son dos argumentos (`./fractol` y `mandelbrot`)
- **argv** tiene dos valores:
    - argv[0] -> `./fractol`
    - argv[1] -> `mandelbrot`.

Estos són los argumentos que, seguidamente, verificaremos si nos los han pasado correctamente.

## 2. t_data data: La estructura principal
```c
t_data  data
```
Esta línea crea una variable llamada `data`, que es una estructura (`struct`) que contiene toda la información importante del programa. Piensa en ella como un "almacén" **datos esenciales** como:
- El nivel de zoom.
- El desplazamiento del fractal.
- La constante c (para Julia).
- La ventana gráfica.
**¿Por qué usamos una estructura?**
Usar una estructura nos permite pasar toda la información a las funciones sin tener que manejar un montón de variables sueltas. Es mas limpio y organizado.

### 2.1 El nivel de zoom.
**¿Qué es?** --> El nivel de zoom controla cuánto "te acercas" o "te alejas" del fractal. Piensa en el fractal como una imagen infinita, con detalles infinitos. El zoom determina qué parte de esa imagen estas viendo y con qué nivel de detalle.
- **Zoom inicial:** Cuando el programa inicia, el zoom es **1.0**, lo que significa que estás viendo el fractal en su escala original (sin acercarte ni alejarte).
- **Zoom mayor a 1.0:** Te estas acercando al fractal. Por ejemplo:
    - Con zoom = 2.0, ves una region mas pequeña pero con más detalle.
- **Zoom menor a 1.0:** Te estas alejando del fractal. Por ejemplo:
    - Con zoom: 0.5, ves una región más grande pero con menos detalle.

**¿Por qué es importante?** --> El fractal es infinito, así que el zoom te permite explorar sus distintas "capas".

### 2.2 El desplazamiento del fractal
**¿Qué es?** --> El desplazamiento (también llamado "offset") se refiere a mover el fractal en el plano complejo. Imagina que el fractal es un lienzo
que puedes desplizar hacia arriba, abajo, izquierda o derecha.
- **Offset inicial:** Al principio, el fractal está "centrado" en la pantalla.
    - `offset[X] = 0.0` --> No hay desplazamiento horizontal.
    - `offset[Y] = 0.0` --> No hay desplazamiento vertical.
- **Cambios de offset:**
    - `offset[X] = 0.5` --> El fractal se mueve hacia la izquierda (en el plano, te desplazas hacia la derecha).
    - `offset[Y] = -0.5` --> El fractal se mueve hacia abajo (en el plano, te desplazas hacia arriba).

**¿Por qué es importante?** Permite explorar partes del fractal que no están en el centro. 
Sin desplazamiento, solo podrías ver el origen del fractal (−2.0−2.0 a +2.0+2.0 en el plano complejo).

#### 2.2.1 Definición del plano complejo.
El plano complejo es un sistema de coordenadas dónde:
- El eje **horizontal** representa los números reales (`Re`).
- El eje **vertical** representa los números imaginarios (`Im`).

Ejemplo:
- El punto (-2.0, -2.0) en el plano complejo representa el número -2.0 -2.0i.
- El punto (1.0, 0.5) representa 1.0 + 0.5i

#### 2.2.2 El rango inicial [-2.0, +2.0]
**Por qué [-2.0, +2.0]**

- Mandelbrot:
    - El fractal de Mandelbrot es **contenido** en un subconjunto del plano complejo:
        - `c` esta entre [-2.0, +2.0] en Re y [-2.0, +2.0] en Im.
    - Fuera de este rango, la función iterativa del fractal no tiene comportamiento interesante (los puntos divergen rápidamente y no contribuyen a la iamgen).
- Julia:
    - Los fractales de Julia también se definen y son más interesantes dentro del rango [−2.0,+2.0].

**Qué significa esto para la ventana gráfica**

Cuando inicializas el fractal sin desplazamiento:
- La esquina superior izquierda de la ventana gráfica corresponde a (−2.0,+2.0) en el plano complejo.
- La esquina inferior derecha corresponde a (+2.0,−2.0).


### 2.3 La constante c (para Julia)

**¿Qué es?**  
En el fractal de Julia, la constante `c` es un número complejo que se mantiene fijo durante las iteraciones. Es el **parámetro clave que define la forma y el comportamiento del fractal.**

**Formato:**  
```text
c = c_real + c_im * i
```
Donde:
- **c_real:** Es la parte real de `c`.
- **c_im:** Es la parte imaginaria de `c`.

#### Ejemplo:  
Si el usuario introduce los valores `0.285` y `-0.01` como argumentos para Julia, entonces:  
```text
c = 0.285 - 0.01i
```

#### ¿Qué hace c? 
En Julia, cada punto del plano complejo (cada píxel) pasa por la fórmula iterativa:  
```text
z_next = (z_current)^2 + c
```
Donde:
- `z_current` es el valor actual del punto.
- `c` es la constante fija.

**¿Por qué es importante?**  
Cambiar el valor de `c` altera completamente la forma del fractal de Julia. 

Esto permite al usuario explorar configuraciones visualmente únicas y descubrir distintas formas y patrones.
- **Esto se refleja directamente en el código** porque `c` es la constante utilizada en las iteraciones para decidir si un punto "pertenece" al fractal o no.
- **Cada valor de c genera un fractal visualmente diferente**, lo que permite explorar configuraciones únicas y patrones completamente nuevos. Sin esta constante, el fractal de Julia no tendría variabilidad ni personalización.

### 2.4 La ventana gráfica
**¿Qué es?**  
La ventana gráfica es el "lienzo" donde se dibuja el fractal. Cada píxel en la ventana gráfica se traduce a un punto en el plano complejo.

**Dimensiones:**
En mi caso:
- Ancho: `WIDTH` 800
- Alto: `HEIGHT` 800

(estas dos se encuentran definidas en **fractol.h**)

**Relación con el plano complejo:**
- La esquina superior izquierda de la ventana gráfica corresponde a un punto en el plano complejo.
- Cada píxel se mapea a una coordenada en el plano complejo usando escalas calculadas.

**Explicación "intermedia"**:
La ventana gráfica es el 'lienzo' donde se dibuja el fractal. Cada píxel en la ventana gráfica se traduce a un punto en el plano complejo. La ventana es gestionada por mlx, mientras que el contenido que se dibuja primero se calcula y almacena en un buffer de imagen llamado img.

Un buffer de imagen es una región de memoria dedicada que actúa como un 'borrador digital', donde se realizan los cálculos y dibujos del fractal antes de enviarlos a la pantalla. Esto asegura un renderizado fluido y evita que el usuario vea parpadeos o actualizaciones parciales durante el cálculo.

## 3. Validación de argumentos (validate_arguments)
```c
static void validate_arguments(int argc, char *argv[])
```
### 3.1 ¿Qué hace esta función?
Esta función verifica si los argumentos pasados al programa son válidos y corresponden a un tipo de fractal soportado (`mandelbrot` o `julia`). Si no se cumplen los requisitos, se muestra un mensaje de error y el programa termina.

### 3.2 Parámetros de entrada
- `argc` -> Número de argumentos pasados al programa desde la línea de comandos.
- `argv` -> Array de cadenas que contiene los argumentos. Ejemplo:
        - `argv[0]` -> Nombre del programa (`./fractol`).
        - `argv[1]` -> Tipo de fractal (`mandelbrot` o `julia`).
        - `argv[2]`, `argv[3]` -> Valores obligatorios de Julia (`c_real` y `c_im`).

### 3.2 ¿Cómo funciona?
1. **Mensajes de error predefinidos:**
La función comienza creando un array `e_msg` con mensajes de error que se utilizarán según el caso.
```c
char *e_msg[5];

e_msg[NO_TYPE] = "No fractal type specified.";
e_msg[INVALID_TYPE] = "Invalid fractal type. Use 'julia' or 'mandelbrot'.";
e_msg[JULIA_ARGS] = "Julia needs: 'julia <c_re> <c_im>'.";
e_msg[JULIA_NUM] = "Julia parameters must be valid numbers.";
e_msg[MANDELBROT_ARGS] = "Mandelbrot needs: 'mandelbrot'.";
```
**Nota:** Las constantes como `NO_TYPE` y `INVALID_TYPE` son valores de una enumeración (enum) definida en **fractol.h**. Una enumeración es una forma de definir un conjunto de valores constantes asociados a nombres legibles. Esto hace que el código sea más claro y fácil de mantener.
2. **¿Faltan argumentos?**
Si no se pasa ningún argumento (es decir, `argc < 2`), se muestra un mensaje de error y se termina el programa:
```c
if (argc < 2)
    exit_with_error(e_msg[NO_TYPE], argv);
```
3. **Validación del tipo de fractal:**
Si el primer argumento es `"mandelbrot"`, la función verifica que no haya argumentos adicionales (`argc != 2`).
Si hay argumentos extras, se muestra un mensaje de error:
```c
if (ft_strcmp(argv[1], "mandelbrot") == 0)
{
    if (argc != 2)
        exit_with_error(e_msg[MANDELBROT_ARGS], argv);
    return;
}
```
Si el primer argumento es `"julia"`, la función verifica que: Se hayan pasado exactamente 4 argumentos (`argc != 4`) y que los valores de `argv[2]` y `argv[3]` sean números válidos, utilizando la función auxiliar `is_valid_number`.
```c
if (ft_strcmp(argv[1], "julia") == 0)
{
    if (argc != 4)
        exit_with_error(e_msg[JULIA_ARGS], argv);
    if (!is_valid_number(argv[2]) || !is_valid_number(argv[3]))
        exit_with_error(e_msg[JULIA_NUM], argv);
}
```
4. **Tipo inválido:**
Si el argumento no es `"mandelbrot"` ni `"julia"`, se muestra un mensaje de error correspondiente:
```c
else
    exit_with_error(e_msg[INVALID_TYPE], argv);
```
### 3.3 ¿Qué pasa si hay un error?
La función utiliza `exit_with_error` para mostrar un mensaje de error específico y termina el programa con un código de error. Esto asegura que el programa no continúe con entradas incorrectas.
```c
static void	exit_with_error(const char *message, char *argv[])
{
	fr_putstr_fd(LIGHT_RED "Error: ", 2);
	fr_putstr_fd((char *)message, 2);
	fr_putstr_fd("\n" RESET, 2);
	fr_putstr_fd(LIGHT_RED "Usage: " LIGHT_GREEN, 2);
	fr_putstr_fd(argv[0], 2);
	fr_putstr_fd(" <fractal_type> [parameters]\n" RESET, 2);
	fr_putstr_fd(LIGHT_RED "Available fractal types:\n" RESET, 2);
	fr_putstr_fd(LIGHT_GOLD "\tmandelbrot" RESET, 2);
	fr_putstr_fd("\t\tDisplays the Mandelbrot set.\n", 2);
	fr_putstr_fd(LIGHT_GOLD "\tjulia [c_re c_im]" RESET, 2);
	fr_putstr_fd("\tDisplays the Julia set.\n", 2);
	fr_putstr_fd(LIGHT_RED "Example: " LIGHT_GREEN, 2);
	fr_putstr_fd(argv[0], 2);
	fr_putstr_fd(" julia 0.285 -0.01\n" RESET, 2);
	exit(EXIT_FAILURE);
}
```
#### 3.4 Ejemplo práctico
Supongamos que ejecutamos:
```bash
./fractol julia 0.285 -0.01
```
- `argc = 4`
- `argv`:
    - `argv[0]` = `"./fractol"`
    - `argv[1]` = `"julia"`
    - `argv[2]` = `"0.285"`
    - `argv[3]` = `"-0.01"`
1. La función verifica que `argv[1] == "julia"`.
2. Comprueba que `argc == 4`.
3. Valida que `"0.285"` y `"-0.01"` sean números válidos.
4. Si todo es correcto, la validación pasa y el programa continúa.
## 4. Configuración del tipo de fractal y parámetros
Esta sección del código se encarga de configurar el tipo de fractal (Julia o Mandelbrot) y, en el caso del fractal de Julia, de inicializar los valores de la constante `c`. Esto es fundamental para que el programa sepa qué tipo de fractal debe generar y qué parámetros utilizar.
```c
if (ft_strcmp(argv[1], "julia") == 0)
{
	data.fractal_type = JULIA;
	data.c[COMPLEX_RE] = ft_atod(argv[2]);
	data.c[COMPLEX_IM] = ft_atod(argv[3]);
}
else if (ft_strcmp(argv[1], "mandelbrot") == 0)
	data.fractal_type = MANDELBROT;
```
### 4.1 ¿Qué hace?
El bloque condicional verifica el argumento `argv[1]` para determinar si el usuario ha seleccionado el fractal de Julia o el de Mandelbrot. Según el resultado, inicializa las variables correspondientes en la estructura data.
#### Comparación del tipo de fractal: Julia
```c
if (ft_strcmp(argv[1], "julia") == 0)
```
Aquí, se utiliza la función ft_strcmp para comparar el argumento `argv[1]` con la cadena "julia". Si son iguales (es decir, el usuario ha solicitado un fractal de Julia), la función devolverá 0, eso quiere decir que la condición se cumple y entraíamos al siguiente punto:
##### Configuración de la estructura data para Julia
```c
data.fractal_type = JULIA;
```
La estructura data contiene el campo `fractal_type`, que se define como un valor de la enumeración `t_fractal_type`. En este caso, se le asigna el valor JULIA, **indicando que el programa debe generar un fractal de Julia**.
##### Conversión de los parámetros de Julia
Los argumentos `argv[2]` y `argv[3]` contienen las partes real e imaginaria de la constante `c`, respectivamente. Estos valores tan importantes que anteriormente hemos hablado de ellos.
Se utiliza la función ft_atod para convertir estas cadenas de texto (como `"0.285"`) en números de punto flotante (como `0.285`).
Luego, se almacenan en los campos `c[COMPLEX_RE]` y `c[COMPLEX_IM]` de la estructura data.

---
#### Comparación del tipo de fractal: Mandelbrot
En cambio si no se cumple, quiere decir que el usuario ha solicitado Mandelbrot.
```c
else if (ft_strcmp(argv[1], "mandelbrot") == 0)
```
##### Configuración de la estructura data para mandelbrot
En este caso es mucho mas facil, se asigna el valor MANDELBROT al campo fractal_type de la estructura data.
```c
data.fractal_type = MANDELBROT;
```
---
### 4.2 Ejemplo práctico
Si la **entrada del usuario:** és la siguiente:
```bash
./fractol julia 0.285 -0.01
```
**Resultados en el programa:**
- `argv[1]` es `"julia"`, por lo que:
  - `data.fractal_type` = `JULIA`.
  - `data.c[COMPLEX_RE]` = `0.285`.
  - `data.c[COMPLEX_IM]` = `-0.01`.

El programa utiliza estos valores para renderizar un fractal de Julia con la constante `c = 0.285 - 0.01i`

## 5. Ciclo principal del programa
Esta sección describe el flujo final del `main`, donde **se configuran los elementos gráficos, se renderiza el fractal, se manejan los eventos de usuario y se inicia el bucle principal del programa**.
```c
	initialize_window(&data, argv);
	render_fractal(&data);
	mlx_key_hook(data.mlx, handle_key, &data);
	mlx_scroll_hook(data.mlx, handle_scroll, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
```
### 5.1 Inicialización de la ventana gráfica
```c
initialize_window(&data, argv);
```
Esta función se encarga de preparar todo lo necesario para que el programa pueda trabajar con gráficos:
1. Creación de la ventana: Utiliza la biblioteca MLX42 para inicializar una ventana de dimensiones predefinidas (en este caso, 800x800 píxeles).
2. Asignación del buffer de imagen: Crea un espacio en memoria (img) donde se dibujará el fractal antes de mostrarlo en la ventana.
3. Valores iniciales: Configura los valores iniciales para el zoom, los desplazamientos (offset) y otros parámetros necesarios.

**¿Por qué es importante?**
Sin esta inicialización, el programa no tendría un área gráfica donde dibujar el fractal ni un contexto para gestionar los eventos.

#### 5.1.1 Creación de la ventana (mlx_init)
```c
data->mlx = mlx_init(WIDTH, HEIGHT, argv[1], false);
if (!data->mlx)
    exit(EXIT_FAILURE);
```

##### ¿Qué hace?
Esta línea inicializa una nueva instancia de MLX42, que crea y gestiona la ventana gráfica del programa.

1. **Parámetros de entrada:**
   - `WIDTH` y `HEIGHT` especifican las dimensiones de la ventana gráfica, que en este caso son 800x800 píxeles.
   - `argv[1]` proporciona el título de la ventana (por ejemplo, `"mandelbrot"` o `"julia"`).
   - `false` indica que la ventana no será redimensionable.

2. **Funcionamiento:**
   - Internamente, la función **reserva recursos** para inicializar el contexto gráfico y crea una ventana con las especificaciones dadas.
   - Si algo falla durante esta inicialización (por ejemplo, falta de memoria o error de configuración), `mlx_init` devuelve `NULL`.

3. **Validación de errores:**
   - Si `mlx_init` retorna `NULL`, significa que la ventana no pudo ser creada. En este caso:
     - El programa finaliza con `exit(EXIT_FAILURE)` para evitar problemas mayores (como intentos de usar recursos no inicializados).

##### ¿Por qué es importante?
Sin esta ventana, el programa no podría mostrar nada en pantalla ni interactuar con el usuario. Además, `mlx_init` devuelve un puntero (`mlx`) que será necesario para todas las funciones de MLX42 posteriores.

#### 5.1.2 Creación del buffer de imagen (mlx_new_image)
```c
data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
if (!data->img)
{
    mlx_terminate(data->mlx);
    exit(EXIT_FAILURE);
}
```

##### ¿Qué hace?
Crea un **buffer de imagen** (almacenado en `data->img`) donde se realizará todo el dibujo antes de mostrarlo en la ventana.

1. **Parámetros de entrada:**
   - `data->mlx`: El puntero al contexto de MLX creado previamente con `mlx_init`.
   - `WIDTH` y `HEIGHT`: Dimensiones del buffer de imagen (en este caso, 800x800 píxeles).

2. **Funcionamiento:**
   - La función **reserva memoria** para un buffer de imagen de las dimensiones dadas.
   - Este buffer actúa como un espacio temporal donde se almacenan los píxeles antes de que sean enviados a la ventana gráfica.

3. **Validación de errores:**
   - Si `mlx_new_image` retorna `NULL`, significa que el buffer de imagen no pudo ser creado (por ejemplo, por falta de memoria).
   - En este caso:
     - Se libera el recurso de la ventana (`mlx_terminate`) para evitar fugas de memoria.
     - El programa se cierra con `exit(EXIT_FAILURE)`.

##### ¿Por qué es importante?
El buffer de imagen es fundamental porque permite realizar los cálculos del fractal sin parpadeos ni interrupciones visibles para el usuario. Esto asegura un renderizado fluido.

#### 5.1.3 Mostrar la imagen en la ventana (mlx_image_to_window)
```c
if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
{
    mlx_terminate(data->mlx);
    exit(EXIT_FAILURE);
}
```

##### ¿Qué hace?
Asocia el buffer de imagen (`data->img`) con la ventana gráfica (`data->mlx`) y muestra su contenido en la posición `(0, 0)`.

1. **Parámetros de entrada:**
   - `data->mlx`: Puntero al contexto de MLX.
   - `data->img`: Puntero al buffer de imagen creado previamente.
   - `0, 0`: Coordenadas de la esquina superior izquierda donde se colocará la imagen.

2. **Funcionamiento:**
   - La función asigna el contenido del buffer de imagen a la ventana gráfica en las coordenadas especificadas.
   - Internamente, también gestiona el orden de renderizado (profundidad Z) para evitar solapamientos no deseados.

3. **Validación de errores:**
   - Si la función retorna `-1`, significa que hubo un error al intentar asociar la imagen con la ventana.
   - En este caso:
     - Se libera el recurso de la ventana (`mlx_terminate`).
     - El programa se cierra con `exit(EXIT_FAILURE)`.

##### ¿Por qué es importante?
Esta operación es la que permite que el fractal sea visible en pantalla. Sin este paso, aunque el cálculo del fractal sea correcto, no se mostraría nada al usuario.

#### 5.1.4 Inicialización de valores
```c
data->offset[OFFSET_X] = 0.0;
data->offset[OFFSET_Y] = 0.0;
data->zoom = 1.0;
```

##### ¿Qué hace?
Establece los valores iniciales para el [desplazamiento](#autotoc_md11) y el [zoom](#autotoc_md9) del fractal.

1. **Desplazamiento** (`offset`):
   - `OFFSET_X` y `OFFSET_Y` controlan el movimiento del fractal en el plano complejo.
   - Al inicializar en `0.0`, el fractal está "centrado".

2. **Zoom:**
   - `zoom` controla el nivel de ampliación del fractal.
   - Al inicializar en `1.0`, se visualiza el fractal en su escala original.

##### ¿Por qué es importante?
Estos valores son esenciales para calcular correctamente las coordenadas del plano complejo y generar el fractal en pantalla.

#### 5.1.5 Resumen de initialize_window
1. **Crea la ventana gráfica:** Se utiliza `mlx_init` para crear una ventana de 800x800 píxeles.
2. **Asigna un buffer de imagen:** `mlx_new_image` crea un área de memoria para realizar los cálculos del fractal.
3. **Muestra la imagen en la ventana:** `mlx_image_to_window` asocia el buffer de imagen con la ventana para que sea visible.
4. **Establece valores iniciales:** Se configuran el zoom y el desplazamiento para que el fractal aparezca centrado y sin ampliación.

#### 5.1.6 ¿Qué debe recordar un desarrollador?
- **Validar retornos:** Siempre comprobar los retornos de `mlx_init`, `mlx_new_image` y `mlx_image_to_window` para manejar posibles fallos.
- **Liberar recursos:** Usar `mlx_terminate` en caso de errores para evitar fugas de memoria.
- **Secuencia correcta:** Primero inicializar MLX, luego el buffer de imagen y finalmente asociarlos con la ventana.

---
### 5.2 Renderización del fractal
```c
void render_fractal(t_data *data)
{
    if (data->fractal_type == JULIA)
        render_julia(data);
    else if (data->fractal_type == MANDELBROT)
        render_mandelbrot(data);
}
```
#### ¿Qué hace esta función?
`render_fractal` es una función delegadora que decide qué tipo de fractal dibujar basándose en el valor de `data->fractal_type` (definido anteriormente). Esto permite que el código sea modular y flexible, separando la lógica de renderización específica para cada fractal.
1. Parámetro de entrada:
- `data`: Es un puntero a la estructura principal `t_data`, que contiene toda la información necesaria, como el tipo de fractal y los valores de zoom, desplazamiento, y buffer de imagen.
2. Decisión basada en el tipo de fractal:
- Si `data->fractal_type` es JULIA, llama a **render_julia(data)** para generar y dibujar un fractal de Julia.
- Si `data->fractal_type` es MANDELBROT, llama a **render_mandelbrot(data)** para generar y dibujar un fractal de Mandelbrot.

#### Modularidad y escalabilidad
Esta función es clave para mantener el código organizado y modular, ya que abstrae las diferencias entre los fractales. Si en el futuro se quiere añadir otro tipo de fractal, solo será necesario:
1. Definir una nueva función de renderización (por ejemplo, `render_tricorn`).
2. Añadir una nueva condición a esta función.
```c
  else if (data->fractal_type == TRICORN)
        render_tricorn(data);
```
---

**Más adelante en la documentación, se explicará en detalle cómo funcionan las funciones de renderización específicas, como `render_julia` y `render_mandelbrot`. En esa sección, analizaremos los algoritmos iterativos utilizados, cómo se manejan los píxeles y cómo se ajustan las coordenadas al plano complejo.**

---

### 5.3 Manejo de eventos con MLX42
Esta sección del código utiliza las funciones de la biblioteca MLX42 para configurar los eventos de usuario y manejar el ciclo principal de la aplicación. Aquí explicaremos cada una de las funciones relacionadas con la gestión de entradas y el bucle principal.
```c
	mlx_key_hook(data.mlx, handle_key, &data);
	mlx_scroll_hook(data.mlx, handle_scroll, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
```

#### 5.3.1 Asignación de eventos de teclado (`mlx_key_hook`)
```c
mlx_key_hook(data.mlx, handle_key, &data);
```

##### ¿Qué hace?
Asocia la función `handle_key` con los eventos de teclado. Cada vez que el usuario presione una tecla, `handle_key` será ejecutada para interpretar y procesar la entrada.

##### Parámetros de mlx_key_hook:
- `mlx`: Puntero a la instancia de MLX, necesaria para configurar el evento en la ventana gráfica.
- `func`: Puntero a la función de callback (en este caso, `handle_key`), que define cómo se manejan los eventos de teclado.
- `param`: Puntero a datos adicionales (en este caso, `&data`), que se pasa como argumento a la función de callback.

##### La función handle_key:
Esta es la implementación personalizada de la función de callback que procesa los eventos de teclado:
```c
void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	else if (keydata.key == MLX_KEY_W)
		data->offset[OFFSET_Y] -= 0.1 / data->zoom;
	else if (keydata.key == MLX_KEY_S)
		data->offset[OFFSET_Y] += 0.1 / data->zoom;
	else if (keydata.key == MLX_KEY_A)
		data->offset[OFFSET_X] -= 0.1 / data->zoom;
	else if (keydata.key == MLX_KEY_D)
		data->offset[OFFSET_X] += 0.1 / data->zoom;
	else if (keydata.key == MLX_KEY_UP)
		data->zoom *= ZOOM_IN;
	else if (keydata.key == MLX_KEY_DOWN)
		data->zoom *= ZOOM_OUT;
	render_fractal(data);
}
```

##### Parámetros de handle_key:
- `mlx_key_data_t keydata`: Estructura que contiene información sobre la tecla presionada, como:
  - `key`: Identificador de la tecla (e.g., `MLX_KEY_W` para la tecla W).
  - `action`: Tipo de acción (presionar, soltar, etc.).
- `void *param`: Un puntero genérico que en este caso apunta a `t_data`, permitiendo modificar los datos del fractal en respuesta a la entrada del usuario.

##### Funcionamiento en este programa:
1. Cierre de la ventana:
   - Si el usuario presiona `ESC`, la ventana se cierra utilizando `mlx_close_window`.
2. Movimiento del fractal:
   - W/S: Mueve el fractal hacia arriba o abajo en el plano complejo.
   - A/D: Mueve el fractal hacia la izquierda o derecha.
3. Zoom:
   - Flecha arriba (`UP`): Aumenta el nivel de zoom, acercándose al fractal.
   - Flecha abajo (`DOWN`): Disminuye el nivel de zoom, alejándose.
4. Renderización:
   - Después de procesar una acción, `render_fractal` se llama para actualizar la ventana con los cambios.

##### ¿Por qué es importante?
Permite que el usuario explore el fractal de manera interactiva en tiempo real, adaptando la visualización según las teclas presionadas.

##### Notas importantes:
- `&data` conecta `handle_key` con la estructura principal del programa, permitiendo que los cambios en el zoom o desplazamiento afecten directamente al fractal.
- El diseño modular de `mlx_key_hook` y `handle_key` asegura que el código sea extensible y fácil de mantener.

---

#### 5.3.2 Asignación de eventos de scroll (mlx_scroll_hook)
```c
mlx_scroll_hook(data.mlx, handle_scroll, &data);
```

##### ¿Qué hace?
Asocia la función `handle_scroll` con los eventos de desplazamiento del ratón (scroll). Esto incluye acciones como mover la rueda del ratón hacia arriba o hacia abajo para realizar zoom en el fractal.

##### Parámetros de mlx_scroll_hook:
- `mlx`: Puntero a la instancia de MLX, necesaria para registrar los eventos de scroll en la ventana gráfica.
- `func`: Puntero a la función de callback (en este caso, `handle_scroll`), que define cómo se manejan los eventos de scroll.
- `param`: Puntero a datos adicionales (en este caso, `&data`), que se pasa como argumento a la función de callback.

##### La función handle_scroll:
Esta es la implementación personalizada de la función de callback para manejar eventos de scroll:
```c
void	handle_scroll(double xdelta, double ydelta, void *param)
{
	t_data	*data;

	(void)xdelta;
	data = (t_data *)param;
	if (ydelta > 0)
		data->zoom *= ZOOM_IN;
	else
		data->zoom *= ZOOM_OUT;
	render_fractal(data);
}
```

##### Parámetros de `handle_scroll`:
- `xdelta`: Cantidad de desplazamiento en el eje horizontal (no utilizado en este caso).
- `ydelta`: Cantidad de desplazamiento en el eje vertical, que determina si el usuario está desplazando hacia arriba o hacia abajo.
  - Un valor positivo indica un desplazamiento hacia arriba.
  - Un valor negativo indica un desplazamiento hacia abajo.
- `param`: Puntero genérico que en este caso apunta a `t_data`, permitiendo modificar los datos del fractal en respuesta al evento de scroll.

##### Funcionamiento en este programa:
1. Zoom in:
   - Si `ydelta > 0` (scroll hacia arriba), el programa aumenta el nivel de zoom multiplicando `data->zoom` por un factor de ampliación (`ZOOM_IN`).
2. Zoom out:
   - Si `ydelta < 0` (scroll hacia abajo), el programa disminuye el nivel de zoom multiplicando `data->zoom` por un factor de reducción (`ZOOM_OUT`).
3. Renderización:
   - Después de ajustar el zoom, se llama a `render_fractal(data)` para actualizar la ventana gráfica con los nuevos valores.

##### ¿Por qué es importante?
El scroll permite que el usuario explore el fractal con mayor fluidez, ajustando el nivel de zoom de manera rápida y precisa. Esto mejora la experiencia interactiva y facilita la exploración de los detalles del fractal.

##### Notas importantes:
- `&data` conecta la función de scroll con los datos principales del fractal, permitiendo modificar parámetros como el zoom en tiempo real.
- Se ignora el desplazamiento horizontal (`xdelta`) ya que en este programa solo interesa el zoom vertical.
- Es importante mantener la función modular para que sea reutilizable o extensible en futuras características.

---

#### 5.3.3 Inicio del bucle principal (mlx_loop)
```c
mlx_loop(data.mlx);
```

##### ¿Qué hace?
Inicia el bucle principal de la aplicación. Este bucle:
1. Procesa los eventos de usuario, como teclado y scroll.
2. Actualiza la ventana gráfica según sea necesario.
3. No se detiene hasta que el usuario cierre la ventana.

##### Parámetros:
- `data.mlx`: Puntero a la instancia de MLX.

##### ¿Por qué es importante?
El bucle principal asegura que la aplicación permanezca activa, respondiendo a eventos en tiempo real y actualizando continuamente la ventana gráfica.

##### Nota:
**El bucle es infinito y solo se detiene cuando el usuario cierra explícitamente la ventana.**

---

#### 5.3.4 Finalización del programa (mlx_terminate)
```c
mlx_terminate(data.mlx);
return (EXIT_SUCCESS);
```

##### ¿Qué hace?
**Libera todos los recursos asignados por MLX, como la ventana, el contexto gráfico y los buffers asociados.**

##### Parámetros:
- `data.mlx`: Puntero a la instancia de MLX.

##### ¿Por qué es importante?
Garantiza que no haya fugas de memoria ni recursos innecesarios en uso al finalizar el programa.

##### Nota importante:
Intentar usar cualquier función de MLX después de llamar a `mlx_terminate` es comportamiento indefinido y puede causar errores graves.

#### 5.3.5 Resumen de manejo de eventos con MLX42
1. **Interacción:**
   - `mlx_key_hook`: Configura los eventos de teclado para mover y ajustar el fractal.
   - `mlx_scroll_hook`: Configura los eventos de scroll para controlar el zoom.
2. **Ciclo principal:**
   - `mlx_loop`: Mantiene el programa activo, procesando eventos y actualizando la ventana.
3. **Liberación de recursos:**
   - `mlx_terminate`: Libera todos los recursos gráficos y finaliza el programa correctamente.