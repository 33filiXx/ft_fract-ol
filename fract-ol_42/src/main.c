#include "../nrc/fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(int argc , char *argv[])
{
    if (argc > 1)
    {
        t_fractol fractol;
        if (pars(argv , argc , &fractol) == 0)
        {
            write(2,"Usage: ./fractol Mandelbrot \n       ./fractol Julia <RealPart> <ImagPart>\n",75);
            exit(1);
        }
        fractol.mlx = mlx_init();
        fractol.mlx_win = mlx_new_window(fractol.mlx, 800, 800, "Hello world!");
        fractol.img.img = mlx_new_image(fractol.mlx, 1920, 1080);
        fractol.img.addr = mlx_get_data_addr(fractol.img.img, &fractol.img.bits_per_pixel, &fractol.img.line_length, &fractol.img.endian);
        if (fractol.fractal_type == 1)
        {

            fractol.x_min = -2.0;
            fractol.x_max =  1.0;
            fractol.y_min = -1.5;
            fractol.y_max =  1.5;
            fractol.max_iter = 50;
        }
        else
        {
            fractol.x_min = -2.0;
            fractol.x_max =  2.0;
            fractol.y_min = -2.0;
            fractol.y_max =  2.0;

        }
        rander_fractol(&fractol);
        mlx_mouse_hook(fractol.mlx_win, mouse_hook, &fractol);
        mlx_hook(fractol.mlx_win, 2, 1L << 0, key_hook, &fractol);
        mlx_hook(fractol.mlx_win, 17, 0L, close_window, &fractol);
        mlx_loop(fractol.mlx);
    } 
    else
        write(2,"Usage: ./fractol Mandelbrot \n       ./fractol Julia <RealPart> <ImagPart>\n",75);
    
    return 0;
}
