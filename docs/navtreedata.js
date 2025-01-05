/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "Fractol", "index.html", [
    [ "Fractol: A Fractal Visualization Project", "index.html", "index" ],
    [ "Funciones Auxiliares", "md_auxiliary__explained.html", [
      [ "1. ft_strcmp", "md_auxiliary__explained.html#autotoc_md1", [
        [ "Definición", "md_auxiliary__explained.html#autotoc_md2", null ],
        [ "¿Qué hace esta función?", "md_auxiliary__explained.html#autotoc_md3", null ],
        [ "Parámetros", "md_auxiliary__explained.html#autotoc_md4", null ],
        [ "Retorno", "md_auxiliary__explained.html#autotoc_md5", null ],
        [ "Detalles del funcionamiento", "md_auxiliary__explained.html#autotoc_md6", null ],
        [ "Ejemplo de uso", "md_auxiliary__explained.html#autotoc_md7", null ],
        [ "¿Por qué es útil?", "md_auxiliary__explained.html#autotoc_md8", null ]
      ] ],
      [ "2. fr_putstr_fd", "md_auxiliary__explained.html#autotoc_md9", [
        [ "Definición", "md_auxiliary__explained.html#autotoc_md10", null ],
        [ "¿Qué hace esta función?", "md_auxiliary__explained.html#autotoc_md11", null ],
        [ "Parámetros", "md_auxiliary__explained.html#autotoc_md12", null ],
        [ "Retorno", "md_auxiliary__explained.html#autotoc_md13", null ],
        [ "Detalles del funcionamiento", "md_auxiliary__explained.html#autotoc_md14", null ],
        [ "Ejemplo de uso", "md_auxiliary__explained.html#autotoc_md15", null ],
        [ "¿Por qué es útil?", "md_auxiliary__explained.html#autotoc_md16", null ]
      ] ],
      [ "3. is_valid_number", "md_auxiliary__explained.html#autotoc_md17", [
        [ "Definición", "md_auxiliary__explained.html#autotoc_md18", null ],
        [ "¿Qué hace esta función?", "md_auxiliary__explained.html#autotoc_md19", null ],
        [ "Parámetros", "md_auxiliary__explained.html#autotoc_md20", null ],
        [ "Retorno", "md_auxiliary__explained.html#autotoc_md21", null ],
        [ "Detalles del funcionamiento", "md_auxiliary__explained.html#autotoc_md22", null ],
        [ "Ejemplo de uso", "md_auxiliary__explained.html#autotoc_md23", null ],
        [ "¿Por qué es útil?", "md_auxiliary__explained.html#autotoc_md24", null ]
      ] ],
      [ "4. calculate_color", "md_auxiliary__explained.html#autotoc_md25", [
        [ "Definición", "md_auxiliary__explained.html#autotoc_md26", null ],
        [ "¿Qué hace esta función?", "md_auxiliary__explained.html#autotoc_md27", null ],
        [ "Parámetros", "md_auxiliary__explained.html#autotoc_md28", null ],
        [ "Retorno", "md_auxiliary__explained.html#autotoc_md29", null ],
        [ "Detalles del funcionamiento", "md_auxiliary__explained.html#autotoc_md30", null ],
        [ "Ejemplo de uso", "md_auxiliary__explained.html#autotoc_md31", null ],
        [ "¿Por qué es útil?", "md_auxiliary__explained.html#autotoc_md32", null ]
      ] ],
      [ "5. calculate_scales_and_limits", "md_auxiliary__explained.html#autotoc_md33", [
        [ "Definición", "md_auxiliary__explained.html#autotoc_md34", null ],
        [ "¿Qué hace esta función?", "md_auxiliary__explained.html#autotoc_md35", null ],
        [ "Parámetros", "md_auxiliary__explained.html#autotoc_md36", null ],
        [ "Detalles del funcionamiento", "md_auxiliary__explained.html#autotoc_md38", [
          [ "1. Cálculo de las escalas", "md_auxiliary__explained.html#autotoc_md39", null ],
          [ "2. Cálculo de los límites iniciales", "md_auxiliary__explained.html#autotoc_md41", null ],
          [ "3. Asignación del buffer de píxeles", "md_auxiliary__explained.html#autotoc_md43", null ]
        ] ],
        [ "Ejemplo práctico", "md_auxiliary__explained.html#autotoc_md45", [
          [ "Supongamos:", "md_auxiliary__explained.html#autotoc_md46", null ],
          [ "Resultado:", "md_auxiliary__explained.html#autotoc_md47", null ]
        ] ],
        [ "Importancia de esta función", "md_auxiliary__explained.html#autotoc_md49", null ]
      ] ]
    ] ],
    [ "Calculos de Julia", "md_julia__calcs.html", [
      [ "1. julia_iterations", "md_julia__calcs.html#autotoc_md54", [
        [ "Definición", "md_julia__calcs.html#autotoc_md55", null ],
        [ "¿Qué hace esta función?", "md_julia__calcs.html#autotoc_md56", [
          [ "Parámetros:", "md_julia__calcs.html#autotoc_md57", null ]
        ] ],
        [ "Detalles del Funcionamiento", "md_julia__calcs.html#autotoc_md59", [
          [ "1. Condición de escape", "md_julia__calcs.html#autotoc_md60", null ],
          [ "2. Actualización del valor de <tt>z</tt>", "md_julia__calcs.html#autotoc_md62", null ]
        ] ],
        [ "Ejemplo de Iteraciones", "md_julia__calcs.html#autotoc_md64", null ]
      ] ],
      [ "2. render_julia_row", "md_julia__calcs.html#autotoc_md65", [
        [ "Definición", "md_julia__calcs.html#autotoc_md66", null ],
        [ "¿Qué hace esta función?", "md_julia__calcs.html#autotoc_md67", null ],
        [ "Parámetros", "md_julia__calcs.html#autotoc_md68", null ],
        [ "Detalles del funcionamiento", "md_julia__calcs.html#autotoc_md70", [
          [ "1. Cálculo de la coordenada real inicial del píxel", "md_julia__calcs.html#autotoc_md71", null ],
          [ "2. Inicialización del número complejo <tt>z</tt>", "md_julia__calcs.html#autotoc_md72", null ],
          [ "3. Ejecución del algoritmo de iteraciones de Julia", "md_julia__calcs.html#autotoc_md73", null ],
          [ "4. Cálculo del color del píxel", "md_julia__calcs.html#autotoc_md74", null ]
        ] ],
        [ "Ejemplo Práctico", "md_julia__calcs.html#autotoc_md76", [
          [ "Supongamos:", "md_julia__calcs.html#autotoc_md77", null ]
        ] ]
      ] ],
      [ "3. render_julia", "md_julia__calcs.html#autotoc_md78", [
        [ "Definición", "md_julia__calcs.html#autotoc_md79", null ],
        [ "¿Qué hace esta función?", "md_julia__calcs.html#autotoc_md80", null ],
        [ "Parámetros", "md_julia__calcs.html#autotoc_md81", null ],
        [ "Detalles del funcionamiento", "md_julia__calcs.html#autotoc_md83", [
          [ "1. Configuración inicial", "md_julia__calcs.html#autotoc_md84", null ],
          [ "2. Iteración sobre cada fila", "md_julia__calcs.html#autotoc_md85", null ]
        ] ],
        [ "Ejemplo Práctico", "md_julia__calcs.html#autotoc_md87", [
          [ "Supongamos:", "md_julia__calcs.html#autotoc_md88", null ],
          [ "Resultado para la fila <tt>y = 100</tt>:", "md_julia__calcs.html#autotoc_md89", null ]
        ] ],
        [ "Importancia del Proceso Completo", "md_julia__calcs.html#autotoc_md91", null ]
      ] ]
    ] ],
    [ "Main Explained", "md_main__explained.html", [
      [ "1. main: punto de entrada.", "md_main__explained.html#autotoc_md93", null ],
      [ "2. t_data data: La estructura principal", "md_main__explained.html#autotoc_md94", [
        [ "2.1 El nivel de zoom.", "md_main__explained.html#autotoc_md95", null ],
        [ "2.2 El desplazamiento del fractal", "md_main__explained.html#autotoc_md96", [
          [ "2.2.1 Definición del plano complejo.", "md_main__explained.html#autotoc_md97", null ],
          [ "2.2.2 El rango inicial [-2.0, +2.0]", "md_main__explained.html#autotoc_md98", null ]
        ] ],
        [ "2.3 La constante c (para Julia)", "md_main__explained.html#autotoc_md99", [
          [ "Ejemplo:", "md_main__explained.html#autotoc_md100", null ],
          [ "¿Qué hace c?", "md_main__explained.html#autotoc_md101", null ]
        ] ],
        [ "2.4 La ventana gráfica", "md_main__explained.html#autotoc_md102", null ]
      ] ],
      [ "3. Validación de argumentos (validate_arguments)", "md_main__explained.html#autotoc_md103", [
        [ "3.1 ¿Qué hace esta función?", "md_main__explained.html#autotoc_md104", null ],
        [ "3.2 Parámetros de entrada", "md_main__explained.html#autotoc_md105", null ],
        [ "3.2 ¿Cómo funciona?", "md_main__explained.html#autotoc_md106", null ],
        [ "3.3 ¿Qué pasa si hay un error?", "md_main__explained.html#autotoc_md107", [
          [ "3.4 Ejemplo práctico", "md_main__explained.html#autotoc_md108", null ]
        ] ]
      ] ],
      [ "4. Configuración del tipo de fractal y parámetros", "md_main__explained.html#autotoc_md109", [
        [ "4.1 ¿Qué hace?", "md_main__explained.html#autotoc_md110", [
          [ "Comparación del tipo de fractal: Julia", "md_main__explained.html#autotoc_md111", [
            [ "Configuración de la estructura data para Julia", "md_main__explained.html#autotoc_md112", null ],
            [ "Conversión de los parámetros de Julia", "md_main__explained.html#autotoc_md113", null ]
          ] ],
          [ "Comparación del tipo de fractal: Mandelbrot", "md_main__explained.html#autotoc_md115", [
            [ "Configuración de la estructura data para mandelbrot", "md_main__explained.html#autotoc_md116", null ]
          ] ]
        ] ],
        [ "4.2 Ejemplo práctico", "md_main__explained.html#autotoc_md118", null ]
      ] ],
      [ "5. Ciclo principal del programa", "md_main__explained.html#autotoc_md119", [
        [ "5.1 Inicialización de la ventana gráfica", "md_main__explained.html#autotoc_md120", [
          [ "5.1.1 Creación de la ventana (mlx_init)", "md_main__explained.html#autotoc_md121", [
            [ "¿Qué hace?", "md_main__explained.html#autotoc_md122", null ],
            [ "¿Por qué es importante?", "md_main__explained.html#autotoc_md123", null ]
          ] ],
          [ "5.1.2 Creación del buffer de imagen (mlx_new_image)", "md_main__explained.html#autotoc_md124", [
            [ "¿Qué hace?", "md_main__explained.html#autotoc_md125", null ],
            [ "¿Por qué es importante?", "md_main__explained.html#autotoc_md126", null ]
          ] ],
          [ "5.1.3 Mostrar la imagen en la ventana (mlx_image_to_window)", "md_main__explained.html#autotoc_md127", [
            [ "¿Qué hace?", "md_main__explained.html#autotoc_md128", null ],
            [ "¿Por qué es importante?", "md_main__explained.html#autotoc_md129", null ]
          ] ],
          [ "5.1.4 Inicialización de valores", "md_main__explained.html#autotoc_md130", [
            [ "¿Qué hace?", "md_main__explained.html#autotoc_md131", null ],
            [ "¿Por qué es importante?", "md_main__explained.html#autotoc_md132", null ]
          ] ],
          [ "5.1.5 Resumen de initialize_window", "md_main__explained.html#autotoc_md133", null ],
          [ "5.1.6 ¿Qué debe recordar un desarrollador?", "md_main__explained.html#autotoc_md134", null ]
        ] ],
        [ "5.2 Renderización del fractal", "md_main__explained.html#autotoc_md136", [
          [ "¿Qué hace esta función?", "md_main__explained.html#autotoc_md137", null ],
          [ "Modularidad y escalabilidad", "md_main__explained.html#autotoc_md138", null ]
        ] ],
        [ "5.3 Manejo de eventos con MLX42", "md_main__explained.html#autotoc_md141", [
          [ "5.3.1 Asignación de eventos de teclado (<tt>mlx_key_hook</tt>)", "md_main__explained.html#autotoc_md142", [
            [ "¿Qué hace?", "md_main__explained.html#autotoc_md143", null ],
            [ "Parámetros de mlx_key_hook:", "md_main__explained.html#autotoc_md144", null ],
            [ "La función handle_key:", "md_main__explained.html#autotoc_md145", null ],
            [ "Parámetros de handle_key:", "md_main__explained.html#autotoc_md146", null ],
            [ "Funcionamiento en este programa:", "md_main__explained.html#autotoc_md147", null ],
            [ "¿Por qué es importante?", "md_main__explained.html#autotoc_md148", null ],
            [ "Notas importantes:", "md_main__explained.html#autotoc_md149", null ]
          ] ],
          [ "5.3.2 Asignación de eventos de scroll (mlx_scroll_hook)", "md_main__explained.html#autotoc_md151", [
            [ "¿Qué hace?", "md_main__explained.html#autotoc_md152", null ],
            [ "Parámetros de mlx_scroll_hook:", "md_main__explained.html#autotoc_md153", null ],
            [ "La función handle_scroll:", "md_main__explained.html#autotoc_md154", null ],
            [ "Parámetros de <tt>handle_scroll</tt>:", "md_main__explained.html#autotoc_md155", null ],
            [ "Funcionamiento en este programa:", "md_main__explained.html#autotoc_md156", null ],
            [ "¿Por qué es importante?", "md_main__explained.html#autotoc_md157", null ],
            [ "Notas importantes:", "md_main__explained.html#autotoc_md158", null ]
          ] ],
          [ "5.3.3 Inicio del bucle principal (mlx_loop)", "md_main__explained.html#autotoc_md160", [
            [ "¿Qué hace?", "md_main__explained.html#autotoc_md161", null ],
            [ "Parámetros:", "md_main__explained.html#autotoc_md162", null ],
            [ "¿Por qué es importante?", "md_main__explained.html#autotoc_md163", null ],
            [ "Nota:", "md_main__explained.html#autotoc_md164", null ]
          ] ],
          [ "5.3.4 Finalización del programa (mlx_terminate)", "md_main__explained.html#autotoc_md166", [
            [ "¿Qué hace?", "md_main__explained.html#autotoc_md167", null ],
            [ "Parámetros:", "md_main__explained.html#autotoc_md168", null ],
            [ "¿Por qué es importante?", "md_main__explained.html#autotoc_md169", null ],
            [ "Nota importante:", "md_main__explained.html#autotoc_md170", null ]
          ] ],
          [ "5.3.5 Resumen de manejo de eventos con MLX42", "md_main__explained.html#autotoc_md171", null ]
        ] ]
      ] ]
    ] ],
    [ "Calculos de Mandelbrot", "md_mandelbrot__calcs.html", [
      [ "1. compute_next_iteration", "md_mandelbrot__calcs.html#autotoc_md175", [
        [ "Definición", "md_mandelbrot__calcs.html#autotoc_md176", null ],
        [ "¿Qué hace esta función?", "md_mandelbrot__calcs.html#autotoc_md177", null ],
        [ "Parámetros", "md_mandelbrot__calcs.html#autotoc_md178", null ],
        [ "Ejemplo Práctico", "md_mandelbrot__calcs.html#autotoc_md179", null ]
      ] ],
      [ "2. mandelbrot_iterations", "md_mandelbrot__calcs.html#autotoc_md181", [
        [ "Definición", "md_mandelbrot__calcs.html#autotoc_md182", null ],
        [ "¿Qué hace esta función?", "md_mandelbrot__calcs.html#autotoc_md183", null ],
        [ "Parámetros", "md_mandelbrot__calcs.html#autotoc_md184", null ],
        [ "Ejemplo Práctico", "md_mandelbrot__calcs.html#autotoc_md185", null ]
      ] ],
      [ "3. mandelbrot_escape_check", "md_mandelbrot__calcs.html#autotoc_md187", [
        [ "Definición", "md_mandelbrot__calcs.html#autotoc_md188", null ],
        [ "¿Qué hace esta función?", "md_mandelbrot__calcs.html#autotoc_md189", null ],
        [ "Parámetros", "md_mandelbrot__calcs.html#autotoc_md190", null ]
      ] ],
      [ "4. render_mandelbrot_row", "md_mandelbrot__calcs.html#autotoc_md192", [
        [ "Definición", "md_mandelbrot__calcs.html#autotoc_md193", null ],
        [ "¿Qué hace esta función?", "md_mandelbrot__calcs.html#autotoc_md194", null ],
        [ "Parámetros", "md_mandelbrot__calcs.html#autotoc_md195", null ]
      ] ],
      [ "5. render_mandelbrot", "md_mandelbrot__calcs.html#autotoc_md197", [
        [ "Definición", "md_mandelbrot__calcs.html#autotoc_md198", null ],
        [ "¿Qué hace esta función?", "md_mandelbrot__calcs.html#autotoc_md199", null ],
        [ "Parámetros", "md_mandelbrot__calcs.html#autotoc_md200", null ]
      ] ]
    ] ],
    [ "Data Structures", "annotated.html", [
      [ "Data Structures", "annotated.html", "annotated_dup" ],
      [ "Data Structure Index", "classes.html", null ],
      [ "Data Fields", "functions.html", [
        [ "All", "functions.html", null ],
        [ "Variables", "functions_vars.html", null ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "Globals", "globals.html", [
        [ "All", "globals.html", null ],
        [ "Functions", "globals_func.html", null ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Enumerations", "globals_enum.html", null ],
        [ "Enumerator", "globals_eval.html", null ],
        [ "Macros", "globals_defs.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"Makefile.html",
"md_main__explained.html#autotoc_md169"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';