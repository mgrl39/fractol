/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 02:00:53 by meghribe          #+#    #+#             */
/*   Updated: 2025/01/04 12:50:42 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief Calculates the scales and limits for rendering the fractal.
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
 * @brief Precomputes the coordinates for the fractal.
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
 * @brief Renders the fractal based on the selected type.
 */
void	render_fractal(t_data *data)
{
	if (data->fractal_type == JULIA)
		render_julia(data);
	else if (data->fractal_type == MANDELBROT)
		render_mandelbrot(data);
}

/**
 * @brief Calculates the color of a pixel based on its iteration count.
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
