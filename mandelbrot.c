/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:20:48 by meghribe          #+#    #+#             */
/*   Updated: 2025/01/05 14:17:32 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @file mandelbrot.c
 * @brief Implementation of the Mandelbrot set rendering.
 *
 * This file contains all the functions necessary to compute and render the
 * Mandelbrot set fractal.
 * The Mandelbrot set is a visual representation off a mathematical formula
 * applied to complex numbers. THe complexity and beauty of its patterns arise
 * from how quickly or slowly each point "escapes" beyond a defined boundary.
 *
 * ### For Technical Users:
 * - **Core Algorithm:** The Mandelbrot set uses the formula `z = z^2 + c`,
 *   where:
 *   - `z` starts at (0, 0) for every point.
 *   - `c` is the complex number corresponding to the pixel's position on the
 *   screen.
 *   - Iterations continue until `|z|2 > 4` (escape condition) or the maximum
 *   	number of iterations is reached.
 * - **Optimization:**
 *   - **Escape Checks:** Early checks prevent unnecessary calculations for
 *   points.
 *   - **Precomputed Coordinates:** Reduces redundant computations of pixel
 *   	coordinates.
 *   - **Row-Based Rendering:** Processes the fractal row by row for efficient
 *   	memory and rendering operations.
 *   - **Color Mapping:** The number of iteerations determines the color of
 *   	each pixexl, creating vibrant and intricaate fractal patterns.
 *
 * ### For Non-Technical Users:
 * - **What is the Mandelbrot Set?**
 *   The Mandelbrot set is a mathematical design created by repeatedly
 *   applying a simple formula to point on a grid. Points that "escape"
 *   quickly create bright colors, while points that stay "trapped"
 *   generate the darker areas of the fractal.
 *
 */
/**
 * @brief Computes the next iteration for a single point in the Mandelbrot set.
 */
static void	compute_next_iteration(t_render_vars *vars, int i)
{
	double	temp_z_re;

	temp_z_re = vars->z_squared[COMPLEX_RE] - vars->z_squared[COMPLEX_IM];
	temp_z_re += vars->c_re[i];
	vars->z[COMPLEX_IM] = (2.0 * vars->z[COMPLEX_RE] * vars->z[COMPLEX_IM]);
	vars->z[COMPLEX_IM] += vars->c_im;
	vars->z[COMPLEX_RE] = temp_z_re;
	vars->z_squared[COMPLEX_RE] = vars->z[COMPLEX_RE] * vars->z[COMPLEX_RE];
	vars->z_squared[COMPLEX_IM] = vars->z[COMPLEX_IM] * vars->z[COMPLEX_IM];
}

/**
 * @brief Performs the iterations for a single point in the Mandelbrot set.
 */
static void	mandelbrot_iterations(t_render_vars *vars, int i)
{
	double	current_magnitude_squared;
	double	escape_radius_squared;

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

/**
 * @brief Performs an early scape check for a point in the Mandelbrot set.
 */
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

/**
 * @brief Renders a single row of the Mandelbrot set.
 */
static void	render_mandelbrot_row(t_render_vars *vars, t_data *data, int y)
{
	int	x;
	int	i;

	x = 0;
	while (x < WIDTH)
	{
		vars->row = vars->pixels + (y * WIDTH + x);
		vars->c_re[0] = vars->start[COMPLEX_RE] + x * vars->scale[SCALE_X];
		vars->c_re[1] = vars->start[COMPLEX_RE];
		vars->c_re[1] += (x + 1) * vars->scale[SCALE_X];
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

/**
 * @brief Renders the Mandelbrot set fractal.
 */
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
