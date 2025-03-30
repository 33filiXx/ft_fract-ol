#include "../nrc/fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



int get_color(int i, int max_iter)
{
    int color;

    if (i == max_iter)
        color = 0x000000;  // Black if the point is in the set
    else
        color = 0xFFFFFF * i / max_iter;  // Gradient from black to white

    return color;
}


int mandelbrot(double cr, double ci, int max_iter)
{
    double zr = 0.0;
    double zi = 0.0;
    int i = 0;

   
    while (i < max_iter)
    {
        double tmp = zr * zr - zi * zi + cr;
        zi = 2.0 * zr * zi + ci;
        zr = tmp;

        if ((zr * zr + zi * zi) > 4.0)
            break;

        i++;
    }

    if (i == max_iter)
        return 0x000000;  
    else
        return get_color(i, max_iter); 
}


void rander_fractol(t_fractol *f)
{
    int x;
    int y;

    y = 0;
    while (y < 800)
    {
        x = 0;
        while (x < 800)
        {
            f->cr = f->x_min + (x / (double)800)  * (f->x_max - f->x_min);
            f->ci = f->y_min + (y / (double)800) * (f->y_max - f->y_min);
            f->color = mandelbrot(f->cr, f->ci, f->max_iter);
            my_mlx_pixel_put(&f->img, x, y, f->color);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(f->mlx, f->mlx_win, f->img.img, 0, 0);
}


int	main(int argc , char *argv[])
{
    if (argc > 1)
    {
        t_fractol fractol;
        if (pars(argv) == 0)
        {
            ft_printf("Usage: ./fractol Mandelbrot \n       ./fractol Julia <RealPart> <ImagPart>\n");
            exit(1);
        }
        fractol.mlx = mlx_init();
        fractol.mlx_win = mlx_new_window(fractol.mlx, 800, 800, "Hello world!");
        fractol.img.img = mlx_new_image(fractol.mlx, 1920, 1080);
        fractol.img.addr = mlx_get_data_addr(fractol.img.img, &fractol.img.bits_per_pixel, &fractol.img.line_length, &fractol.img.endian);
        fractol.x_min = -2.0;
        fractol.x_max =  1.0;
        fractol.y_min = -1.5;
        fractol.y_max =  1.5;
        fractol.max_iter = 50;
        rander_fractol(&fractol);
        mlx_loop(fractol.mlx);
    } 
    else
        ft_printf("Usage: ./fractol Mandelbrot \n       ./fractol Julia <RealPart> <ImagPart>\n");
    
    return 0;
}
