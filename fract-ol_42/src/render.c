/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:21:15 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/04/09 23:01:44 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nrc/fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_color(int i, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (i == max_iter)
		return (0x000000);
	t = (double)i / max_iter;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((r << 16) | (g << 8) | b);
}

int	mandelbrot(double cr, double ci, int max_iter)
{
	double	zr;
	double	zi;
	int		i;
	double	tmp;

	zr = 0.0;
	zi = 0.0;
	i = 0;
	while (i < max_iter)
	{
		tmp = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci;
		zr = tmp;
		if ((zr * zr + zi * zi) > 4.0)
			break ;
		i++;
	}
	if (i == max_iter)
		return (0x000000);
	else
		return (get_color(i, max_iter));
}

int	julia(double zr, double zi, double jr, double ji)
{
	int		i;
	double	tmp;

	i = 0;
	while (i < JULIA_MAX_ITER)
	{
		tmp = zr * zr - zi * zi + jr;
		zi = 2.0 * zr * zi + ji;
		zr = tmp;
		if ((zr * zr + zi * zi) > 4.0)
			break ;
		i++;
	}
	if (i == JULIA_MAX_ITER)
		return (0x000000);
	return (get_color(i, JULIA_MAX_ITER));
}
int	burningship(double cr, double ci, int max_iter)
{
	double	zr;
	double	zi;
	int		i;
	double	tmp;

	zr = 0.0;
	zi = 0.0;
	i = 0;
	while (i < max_iter)
	{
		tmp = zr * zr - zi * zi + cr;
		zi = fabs(2.0 * zr * zi + ci);
		zr = fabs(tmp);
		if ((zr * zr + zi * zi) > 4.0)
			break ;
		i++;
	}
	if (i == max_iter)
		return (0x000000);
	else
		return (get_color(i, max_iter));
}
void	rander_fractol(t_fractol *f)
{
	double (x_range), (y_range);
	int (x), (y);
	x_range = f->x_max - f->x_min;
	y_range = f->y_max - f->y_min;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			f->cr = f->x_min + (x / (double)WIDTH) * x_range;
			f->ci = f->y_min + (y / (double)HEIGHT) * y_range;   
			if (f->fractal_type == 1)
				f->color = mandelbrot(f->cr, f->ci, f->max_iter);
			else if (f->fractal_type == 2)
				f->color = julia(f->cr, f->ci, f->jr, f->ji);
			else if (f->fractal_type == 3)
				f->color = burningship(f->cr, f->ci, f->max_iter);
			my_mlx_pixel_put(&f->img, x, y, f->color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx, f->mlx_win, f->img.img, 0, 0);
}
