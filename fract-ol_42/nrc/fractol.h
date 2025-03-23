#ifndef FRACTOL_H
# define FRACTOL_H

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

# include "../../minilibx-linux/mlx.h"

#endif