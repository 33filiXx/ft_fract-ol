#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
#include <unistd.h>
# include <stddef.h>
# include "../../minilibx-linux/mlx.h"
# include "../../libft/libft.h"

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
    void    *mlx;       // the MLX connection
    void    *mlx_win;       // the window pointer
    t_data  img;            // embed t_data struct here for image info
    
    double  x_min;
    double  x_max;
    double  y_min;
    double  y_max;
    
	int color;
    int     max_iter;
    int     fractal_type;   // e.g. 0 = Mandelbrot, 1 = Julia
    
    double  cr;            // Julia constant real part (if needed)
    double  ci;            // Julia constant imaginary part
}   t_fractol;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}		t_vars;

int pars(char **str );


#endif