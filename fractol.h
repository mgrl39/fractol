/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:53:33 by meghribe          #+#    #+#             */
/*   Updated: 2025/01/04 13:25:50 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/* ----------------------------- Includes ----------------------------------- */
# include "MLX42/MLX42.h"
# include <limits.h>
# include <stdlib.h>

/* --------------------------- Enumerations -------------------------------- */
/* Fractal types */
typedef enum e_fractal_type
{
	MANDELBROT,
	JULIA,
}	t_fractal_type;

/**
 * @brief Indices for offsets in the x and y directions.
 */
typedef enum e_offset_index
{
	OFFSET_X,
	OFFSET_Y,
}	t_offset_index;

/**
 * @brief Indices for scaling factors in the x and y directions.
 */
typedef enum e_scale_index
{
	SCALE_X,
	SCALE_Y,
}	t_scale_index;

/**
 * @brief Indices for complex numbers (real and imaginary) 
 */
typedef enum e_complex_index
{
	COMPLEX_RE,
	COMPLEX_IM,
}	t_complex_index;

/**
 * @brief Flags for validating numbers.
 */
typedef enum e_number_flags
{
	HAS_DIGIT,
	HAS_POINT,
}	t_number_flags;

/**
 * @brief Error messages used for input validation.
 */
enum e_err_msg
{
	NO_TYPE,
	INVALID_TYPE,
	JULIA_ARGS,
	JULIA_NUM,
	MANDELBROT_ARGS,
};

/* ------------------------- Structures Definitions ------------------------ */
/**
 * @brief Represents an RGB color.
 */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

/**
 * @brief Data structure for fractal rendering
 */
typedef struct s_data
{
	double			zoom;
	double			c[2];
	double			offset[2];
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_fractal_type	fractal_type;
}	t_data;

/**
 * @brief Variables used for fractal rendering calculations.
 */
typedef struct s_render_vars
{
	int			iterations;
	double		scale[2];
	double		start[2];
	double		z[2];
	double		z_squared[2];
	double		c_re[2];
	double		c_re_centered;
	double		c_im;
	uint32_t	*pixels;
	uint32_t	*row;
}	t_render_vars;

/**
 * @brief Helper structure for string-to-double conversion.
 */
typedef struct s_atod_data
{
	int		i;
	int		sign;
	double	result;
	double	divisor;
	double	fraction;
}	t_atod_data;

/* ---------------------------- Function Prototypes ------------------------ */
/**
 * @brief Calculates scales and limits for rendering fractals.
 */
void	calculate_scales_and_limits(t_render_vars *vars, t_data *data);

/**
 * @brief Precomputes coordinates for fractal rendering.
 */
int		precompute_coords(double **c_re, double **c_im, t_render_vars *vars);

/**
 * @brief Calculates the color based on the number of iterations.
 */
int		calculate_color(int iterations);

/**
 * @brief Converts a string to a double.
 */
double	ft_atod(const char *str);

/**
 * @brief Compares two strings.
 */
int		ft_strcmp(const char *s1, const char *s2);

/**
 * @brief Writes a string to a file descriptor.
 */
int		fr_putstr_fd(char *s, int fd);

/* Renderers */
/**
 * @brief Render the specified fractal.
 */
void	render_fractal(t_data *data);

/**
 * @brief Render the Mandelbrot fractal.
 */
void	render_mandelbrot(t_data *data);

/**
 * @brief Renders the Julia fractal.
 */
void	render_julia(t_data *data);

/**
 * @brief Handles key inputs.
 */
void	handle_key(mlx_key_data_t keydata, void *param);

/**
 * @brief Handles scroll inputs.
 */
void	handle_scroll(double xdelta, double ydelta, void *param);

/* ---------------------------- Constants ---------------------------------- */
# define WIDTH				800
# define HEIGHT				WIDTH
# define ZOOM_IN			1.1
# define ZOOM_OUT			0.9
# define FRACTAL_LIMIT		4.0
# define MAX_ITERATIONS		75
# define RESET				"\033[0m"
# define LIGHT_RED			"\033[38;5;203m"
# define LIGHT_GOLD			"\033[38;5;220m"
# define LIGHT_GREEN		"\033[38;5;120m"

#endif
