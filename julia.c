/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:09:26 by meghribe          #+#    #+#             */
/*   Updated: 2025/01/04 12:38:39 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief Performs the iterations for a single point in the Julia set.
 */
static void	julia_iterations(t_render_vars *vars, t_data *data)
{
	double	temp_z_re;

	vars->iterations = 0;
	while (vars->z_squared[COMPLEX_RE] + vars->z_squared[COMPLEX_IM] <= 4.0 && \
			vars->iterations < MAX_ITERATIONS)
	{
		temp_z_re = vars->z_squared[COMPLEX_RE];
		temp_z_re -= vars->z_squared[COMPLEX_IM];
		temp_z_re += data->c[COMPLEX_RE];
		vars->z[COMPLEX_IM] = 2.0 * vars->z[COMPLEX_RE] * \
			vars->z[COMPLEX_IM] + data->c[COMPLEX_IM];
		vars->z[COMPLEX_RE] = temp_z_re;
		vars->z_squared[COMPLEX_RE] = vars->z[COMPLEX_RE] * vars->z[COMPLEX_RE];
		vars->z_squared[COMPLEX_IM] = vars->z[COMPLEX_IM] * vars->z[COMPLEX_IM];
		vars->iterations++;
	}
}

/**
 * @brief Renders a single row of the Julia set.
 */
static void	render_julia_row(t_render_vars *vars, t_data *data, int y)
{
	int	x;

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

/**
 * @brief Renders the Julia set fractal.
 */
void	render_julia(t_data *data)
{
	t_render_vars	vars;
	int				y;

	calculate_scales_and_limits(&vars, data);
	y = 0;
	while (y < HEIGHT)
	{
		vars.c_im = vars.start[COMPLEX_IM] + y * vars.scale[SCALE_Y];
		render_julia_row(&vars, data, y++);
	}
}
