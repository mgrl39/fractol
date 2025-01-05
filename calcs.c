/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 02:00:53 by meghribe          #+#    #+#             */
/*   Updated: 2025/01/05 13:19:20 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @file calcs.c
 * @brief Core calculations for fractal rendering.
 *
 * This file contains the functions responsible for performing the core
 * calculations required to render fractals. It handles:
 * - Scaling and positioning the fractal within the rendering window.
 * - Precomputing the coordinates ffor each pixel to optimize rendering
 *   performance.
 * - Rendering the fractal by delegating to specific algorithms
 *   (Julia or Mandelbrot).
 * - Mapping iteration counts to colors for visually representing 
 *   fractal complexity.
 *
 *   For non-technical users:
 *   - This file performs the "math magic" that powers the fractal visuals,
 *   	calculating where and howw the fractal is drawn and colored on 
 *   	the screen.
 */

/**
 * @brief Calculates the scales and starting points for the fractal rendering.
 *
 * This function determines how the fractal is scaled and positioned on the
 * screen.
 * It computes the scale factors for each pixel and establishes the
 * starting points ffor the real and imaginary part of the fractal based on the
 * zoom level and offsets.
 *
 * For non-technical users:
 * - Think of it as setting the "zoom" and "pam" for the fractal to display it
 *   correctly on the screen.
 *
 * @param vars Pointer to the rendering variables structure.
 * @param data Pointer to the main data structure containing fractal 
 * 	information.
 */
void	calculate_scales_and_limits(t_render_vars *vars, t_data *data)
{
	vars->scale[SCALE_X] = 4.0 / (WIDTH * data->zoom);
	vars->scale[SCALE_Y] = 4.0 / (HEIGHT * data->zoom);
	vars->start[COMPLEX_RE] = -2.0 / data->zoom + data->offset[OFFSET_X];
	vars->start[COMPLEX_IM] = -2.0 / data->zoom + data->offset[OFFSET_Y];
	vars->pixels = (uint32_t *)data->img->pixels;
}

/**
 * @brief Precomputes the coordinates for each pixel in the fractal.
 *
 * This function calculates the real and imaginary parts of the fractal for
 * each pixel on the screen, storing them in arrays for quick access during
 * rendering.
 * It ensures that every point is prepared for the fractal calculations.
 *
 * For non-technical users:
 * - Imagine this as creating a "grid" of points where the fractal will be
 *   drawn. This points tell the program where to caalculate the colors.
 *
 * @param c_re Pointer to the array storing real coordinates.
 * @param c_im Pointer to the array storing imaginary coordinates.
 * @param vars Pointer to the rendering variables structure.
 * @return Returns 1 on success, or 0 if memory allocation fails.
 */
int	precompute_coords(double **c_re, double **c_im, t_render_vars *vars)
{
	int	i;

	*c_re = (double *)malloc(WIDTH * sizeof(double));
	*c_im = (double *)malloc(HEIGHT * sizeof(double));
	if (!(*c_re) || !(*c_im))
		return (free(*c_re), free(*c_im), 0);
	i = -1;
	while (++i < WIDTH)
		(*c_re)[i] = vars->start[COMPLEX_RE] + i * vars->scale[SCALE_X];
	i = -1;
	while (++i < HEIGHT)
		(*c_im)[i] = vars->start[COMPLEX_IM] + i * vars->scale[SCALE_Y];
	return (1);
}

/**
 * @brief Renders the chosen fractal on the screen.
 *
 * This function selects the appropiate rendering algorithm based on the fractal
 * type chosen by the user (Julia or Mandelbrot) and renders it on the screen.
 *
 * For non-technical users:
 * 	- Depending on the type of fractal (Julia or Mandelbrot), this function
 * 	draws the chosen fractal pattern for you to see.
 *
 * @param data Pointer to the main data structure containing fractal and
 * rendering details.
 */
void	render_fractal(t_data *data)
{
	if (data->fractal_type == JULIA)
		render_julia(data);
	else if (data->fractal_type == MANDELBROT)
		render_mandelbrot(data);
}

/**
 * @brief Calculates the color of a pixel based on how many iterations it takes
 * to "escape".
 *
 * This function determines the color of each pixel in the fractal by mapping
 * the iteration count (how many steps we are needed to reach a threshold)
 * to a color gradient.
 *
 * For non-technical users:
 * - The function decides the color of each pooint in the fractal, creating the
 *   beautiful patterns you see based on how "complex" the point is.
 *
 * @param iterations Number of iterations required for the opint to "escape".
 * @return Returns the calculated color as an integer.
 */
int	calculate_color(int iterations)
{
	double	it_count;
	int		base_gray;
	t_color	color;

	it_count = (double)iterations / MAX_ITERATIONS;
	base_gray = (30 + 190 * (it_count * (1 - 0.2 * it_count)));
	color.r = base_gray - (5 * (1 - it_count) * it_count * it_count);
	color.g = base_gray - (10 * (1 - it_count) * (1 - it_count));
	color.b = base_gray - (15 * (1 - it_count) * it_count);
	return ((0xFF << 24) | (color.r << 16) | (color.g << 8) | color.b);
}
