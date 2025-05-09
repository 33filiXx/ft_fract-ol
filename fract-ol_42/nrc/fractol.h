/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:20:46 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/04/10 15:53:42 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../../libft/libft.h"
# include "../../minilibx-linux/mlx.h"
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 150
# define JULIA_MAX_ITER 50

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

}			t_data;

typedef struct s_fractol
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
	double	zoom;
	double	x_offset;
	double	y_offset;
	double	mx;
	double	my;

	int		color;
	int		max_iter;
	int		fractal_type;

	double	cr;
	double	ci;
	double	ji;
	double	jr;
}			t_fractol;

int			pars(char **str, int argc, t_fractol *f);
int			mouse_hook(int button, int x, int y, void *param);
int			key_hook(int keycode, t_fractol *f);
int			close_window(t_fractol *f);
int			get_color(int i, int max_iter);
int			mandelbrot(double cr, double ci, int max_iter);
int			julia(double zr, double zi, double jr, double ji);
void		rander_fractol(t_fractol *f);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			ft_strcmp(char *s1, char *s2);
int			skip(char *s, long *sign);
double		ft_atof(char *s);
void		cleanup_and_exit(t_fractol *fractol, int set);
int			burningship(double cr, double ci, int max_iter);
void		check_ponit(char **str);
int			check_p_m(char *str);

#endif