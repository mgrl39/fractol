/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:32:45 by meghribe          #+#    #+#             */
/*   Updated: 2025/01/04 16:33:38 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <unistd.h>

/**
 * @brief Converts a string to a floating-point number.
 */
double	ft_atod(const char *str)
{
	t_atod_data	d;

	d.result = 0.0;
	d.fraction = 0.0;
	d.divisor = 10.0;
	d.sign = 1;
	d.i = 0;
	while (str[d.i] == 32 || (str[d.i] >= 9 && str[d.i] <= 13))
		d.i++;
	if (str[d.i] == '-' || str[d.i] == '+')
		if (str[d.i++] == '-')
			d.sign = -1;
	while (str[d.i] >= '0' && str[d.i] <= '9')
		d.result = d.result * 10.0 + (str[d.i++] - '0');
	if (str[d.i] == '.')
	{
		d.i++;
		while (str[d.i] >= '0' && str[d.i] <= '9')
		{
			d.fraction += (str[d.i] - '0') / d.divisor;
			d.divisor *= 10.0;
			d.i++;
		}
	}
	return (d.sign * (d.result + d.fraction));
}

/**
 * @brief Compares two strings.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (s1[i] - s2[i]);
}

/*
 * @brief Handles keyboard input.
 */
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
	if (data->zoom < 1e-5)
		data->zoom = 1e-5;
	render_fractal(data);
}

/**
 * @brief Handles mouse scroll input for zooming.
 */
void	handle_scroll(double xdelta, double ydelta, void *param)
{
	t_data	*data;

	(void)xdelta;
	data = (t_data *)param;
	if (ydelta > 0)
		data->zoom *= ZOOM_IN;
	else
		data->zoom *= ZOOM_OUT;
	if (data->zoom < 1e-5)
		data->zoom = 1e-5;
	render_fractal(data);
}

/**
 * @brief Writes a string to a file descriptor and returns 
 */
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
