# Fractol: A Fractal Visualization Project

Fractol is a fractal visualization tool written in C that leverages the MLX42 graphics library for rendering complex and stunning fractals. The project supports the generation of the Mandelbrot and Julia sets, with interactive controls for zooming, panning, and exploring these fascinating mathematical structures.

## Overview

Fractals are infinitely complex patterns that are self-similar across different scales. They are created by repeating a simple mathematical process over and over in an ongoing feedback loop. Fractol uses this principle to generate visually captivating fractal images.

### Supported Fractals
- Mandelbrot Set: A set of complex numbers that do not diverge when iteratively applied to the equation `z_(n+1) = z_n^2 + c`, starting with `z_0 = 0`.
- Julia Set: A family of fractals defined for a fixed complex constant `c`, iterating over `z_(n+1) = z_n^2 + c`.

## Mathematical Foundation

### Complex Numbers
Fractals rely on complex numbers, which have two components:
- **Real part (Re)**
- **Imaginary part (Im)**

Complex numbers can be represented as `z = a + bi`, where:
- `a` is the real component.
- `b` is the imaginary component.
- `i` is the square root of -1.

### Iteration and Divergence
The fundamental concept in fractal generation is iteration:
1. Start with an initial complex number `z_0`.
2. Iteratively apply the equation `z_(n+1) = z_n^2 + c`.
3. Stop if the magnitude of `z`, given by `|z|^2`, is greater than 4 (escape condition) or if the maximum number of iterations is reached.

The number of iterations before escape determines the color of a pixel, creating the fractal's intricate patterns.

### Coordinate Mapping
The fractal exists in the complex plane, but pixels are rendered in a 2D screen coordinate system. Fractol maps each pixel to a corresponding complex number based on:
- The screen resolution.
- The zoom level.
- The viewport offset.

## Project Structure

### Core Files
- `main.c`: Program entry point, argument validation, and MLX42 initialization.
- `calcs.c`: Core calculations for fractal scaling, limits, and color determination.
- `julia.c`: Logic for rendering the Julia set.
- `mandelbrot.c`: Logic for rendering the Mandelbrot set.
- `utils.c`: Helper functions for input handling, number parsing, and string comparison.
- `fractol.h`: Header file containing declarations, structures, and constants.

### Key Concepts

#### Fractal Rendering
1. **Scaling and Limits**:
   - The `calculate_scales_and_limits` function determines the scales and starting points for each axis of the fractal.
   - The scales adjust based on the zoom level to refine the detail as the user zooms in or out.

2. **Precomputed Coordinates**:
   - The `precompute_coords` function calculates the complex coordinates for each pixel row in advance, improving efficiency.

3. **Rendering**:
   - For the Julia set (`render_julia`) and Mandelbrot set (`render_mandelbrot`), Fractol iterates through each pixel, computes whether it escapes, and assigns a color based on the number of iterations.

#### Color Mapping
The color of each pixel is determined by the number of iterations before escape. A smooth gradient effect is applied using:
- Normalized Iterations: Proportional mapping of the iteration count to a color gradient.
- ARGB Encoding: Colors are represented in ARGB format for rendering.

#### Interactive Controls
- **Keyboard**:
  - Arrow keys: Pan the viewport.
  - WASD: Adjust the offset in finer increments.
  - Escape: Exit the application.
  - Up/Down: Zoom in/out.
- **Mouse**:
  - Scroll: Zoom in/out at the cursor's location.

## How to Use

### Build and Run
1. Compile the project using `make`:
   ```bash
   make
   ```
2. Run the program:
   ```bash
   ./fractol <fractal_type> [parameters]
   ```
   Example:
   ```bash
   ./fractol julia 0.285 -0.01
   ```
    Example 2:
   ```bash
   ./fractol mandelbrot
   ```

### Fractal Types
- **mandelbrot**: Generates the Mandelbrot set.
- **julia `<c_re> <c_im>`**: Generates a Julia set with the given complex number.

## Technical Highlights

### Dynamic Scaling
Fractol dynamically adjusts the scale of the fractal based on the zoom level and screen resolution, ensuring high-detail rendering at any zoom level.

### Early Escape Optimization
The Mandelbrot implementation includes early escape checks for points within known regions of the set, significantly speeding up rendering.

### Multi-Precision Calculations
To maintain precision during deep zoom levels, calculations are performed using double-precision floating-point numbers.
