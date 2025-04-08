/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:20:40 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/04/08 17:31:17 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nrc/fractol.h"

void	cleanup_and_exit(t_fractol *fractol, int set)
{
	if (fractol->img.img)
	{
		if (set == 1)
			write(2, "problem with  malloc", 21);
		mlx_destroy_image(fractol->mlx, fractol->img.img);
	}
	if (fractol->mlx_win)
	{
		if (set == 1)
			write(2, "problem with  malloc", 21);
		mlx_destroy_window(fractol->mlx, fractol->mlx_win);
	}
	if (fractol->mlx)
	{
		if (set == 1)
			write(2, "problem with  malloc", 21);
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
	}
	exit(0);
}

void	set_data(t_fractol *fractol)
{
	if (fractol->fractal_type == 1)
	{
		fractol->x_min = -2.0;
		fractol->x_max = 1.0;
		fractol->y_min = -1.5;
		fractol->y_max = 1.5;
		fractol->max_iter = 50;
	}
	else
	{
		fractol->x_min = -2.0;
		fractol->x_max = 2.0;
		fractol->y_min = -2.0;
		fractol->y_max = 2.0;
	}
}

void	check_mlx(t_fractol *fractol)
{
	fractol->mlx = mlx_init();
	if (!fractol->mlx)
		cleanup_and_exit(fractol, 1);
	fractol->mlx_win = mlx_new_window(fractol->mlx, 800, 800, "Hello world!");
	if (!fractol->mlx_win)
		cleanup_and_exit(fractol, 1);
	fractol->img.img = mlx_new_image(fractol->mlx, 1920, 1080);
	if (!fractol->img.img)
		cleanup_and_exit(fractol, 1);
	fractol->img.addr = mlx_get_data_addr(fractol->img.img,
			&fractol->img.bits_per_pixel, &fractol->img.line_length,
			&fractol->img.endian);
	if (!fractol->img.addr)
		cleanup_and_exit(fractol, 1);
}

void	rander_hooks(t_fractol *fractol)
{
	set_data(fractol);
	rander_fractol(fractol);
	mlx_mouse_hook(fractol->mlx_win, mouse_hook, fractol);
	mlx_hook(fractol->mlx_win, 2, 1L << 0, key_hook, fractol);
	mlx_hook(fractol->mlx_win, 17, 0L, close_window, fractol);
	mlx_loop(fractol->mlx);
	cleanup_and_exit(fractol, 0);
}

int	main(int argc, char *argv[])
{
	t_fractol	fractol;

	if (argc > 1)
	{
		if (pars(argv, argc, &fractol) == 0)
		{
			write(2, "Usage: ./fractol mandelbrot\n.", 30);
			write(2, "/fractol julia <RealPart> <ImagPart>", 37);
			exit(1);
		}
		check_mlx(&fractol);
		rander_hooks(&fractol);
	}
	else
	{
		write(2, "Usage: ./fractol mandelbrot\n.", 30);
		write(2, "/fractol julia <RealPart> <ImagPart>", 37);
	}
	return (0);
}
