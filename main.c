/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 12:47:18 by meghribe          #+#    #+#             */
/*   Updated: 2025/01/04 16:33:20 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief Checks if a string is a valid number.
 */
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

/**
 * @brief Prints an error message and exists the program.
 */
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

/**
 * @brief Validates the command-line arguments.
 */
static void	validate_arguments(int argc, char *argv[])
{
	char			*e_msg[5];

	e_msg[NO_TYPE] = "No fractal type specified.";
	e_msg[INVALID_TYPE] = "Invalid fractal type. Use 'julia' or 'mandelbrot'.";
	e_msg[JULIA_ARGS] = "Julia needs: 'julia <c_re> <c_im>'.";
	e_msg[JULIA_NUM] = "Julia parameters must be valid numbers.";
	e_msg[MANDELBROT_ARGS] = "Mandelbrot needs: 'mandelbrot'.";
	if (argc < 2)
		exit_with_error(e_msg[NO_TYPE], argv);
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
	{
		if (argc != 2)
			exit_with_error(e_msg[MANDELBROT_ARGS], argv);
		return ;
	}
	if (ft_strcmp(argv[1], "julia") == 0)
	{
		if (argc != 4)
			exit_with_error(e_msg[JULIA_ARGS], argv);
		if (!is_valid_number(argv[2]) || !is_valid_number(argv[3]))
			exit_with_error(e_msg[JULIA_NUM], argv);
	}
	else
		exit_with_error(e_msg[INVALID_TYPE], argv);
}

/**
 * @brief Initializes the MLX42 window and image.
 */
static void	initialize_window(t_data *data, char *argv[])
{
	if ((data->c[COMPLEX_RE] > 2.0 || data->c[COMPLEX_RE] < -2
			|| data->c[COMPLEX_IM] > 2.0 || data->c[COMPLEX_IM] < -2))
	{
		fr_putstr_fd(LIGHT_GOLD "Warning: The values for Julia are", 1);
		fr_putstr_fd(" outside the common range [-2.0, 2.0]\n", 1);
		fr_putstr_fd(RESET "This may produce unusual or", 1);
		fr_putstr_fd(" less interesting fractals.\n", 1);
	}
	data->mlx = mlx_init(WIDTH, HEIGHT, argv[1], false);
	if (!data->mlx)
		exit (EXIT_FAILURE);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		mlx_terminate(data->mlx);
		exit (EXIT_FAILURE);
	}
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_terminate(data->mlx);
		exit (EXIT_FAILURE);
	}
	data->offset[OFFSET_X] = 0.0;
	data->offset[OFFSET_Y] = 0.0;
	data->zoom = 1.0;
}

/**
 * @brief Main function.
 * - Validates the command-line arguments.
 * - Initializes the fractal type and parameters.
 * - Sets up the rendering environment and renders the fractal.
 * - Configures event hooks and starts the main event loop.
 */
int	main(int argc, char *argv[])
{
	t_data	data;
	char	*error;

	validate_arguments(argc, argv);
	if (ft_strcmp(argv[1], "julia") == 0)
	{
		error = "Julia parameters must be valid numbers.";
		data.fractal_type = JULIA;
		data.c[COMPLEX_RE] = ft_atod(argv[2]);
		data.c[COMPLEX_IM] = ft_atod(argv[3]);
		if (data.c[COMPLEX_RE] > INT_MAX || data.c[COMPLEX_RE] < INT_MIN)
			return (exit_with_error(error, argv), 1);
		if (data.c[COMPLEX_IM] > INT_MAX || data.c[COMPLEX_IM] < INT_MIN)
			return (exit_with_error(error, argv), 1);
	}
	else if (ft_strcmp(argv[1], "mandelbrot") == 0)
		data.fractal_type = MANDELBROT;
	initialize_window(&data, argv);
	render_fractal(&data);
	mlx_key_hook(data.mlx, handle_key, &data);
	mlx_scroll_hook(data.mlx, handle_scroll, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
