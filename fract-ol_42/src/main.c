#include "../nrc/fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



int	get_color(int i, int max_iter)
{
	if (i == max_iter)
		return 0x000000;

	double t = (double)i / max_iter;

	int r = (int)(9 * (1 - t) * t * t * t * 255);
	int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

	return (r << 16) | (g << 8) | b;
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

int	julia(double zr, double zi, double jr, double ji)
{
    // A fixed iteration count inside the function.
    // Not passed as a param, not a global, no struct usage.
  

    int i = 0;
    while (i < JULIA_MAX_ITER)
    {
        double tmp = zr * zr - zi * zi + jr;
        zi = 2.0 * zr * zi + ji;
        zr = tmp;
        if ((zr * zr + zi * zi) > 4.0)
            break;
        i++;
    }
    if (i == JULIA_MAX_ITER)
        return 0x000000;
    return get_color(i, JULIA_MAX_ITER);
}

void rander_fractol(t_fractol *f)
{
    int x, y;
    double x_range = f->x_max - f->x_min;
    double y_range = f->y_max - f->y_min;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            double cr = f->x_min + (x / (double)WIDTH) * x_range;
            double ci = f->y_min + (y / (double)HEIGHT) * y_range;

            if (f->fractal_type == 1) // Mandelbrot
            {
                f->color = mandelbrot(cr, ci, f->max_iter);
            }
            else // fractal_type == 2 => Julia
            {
                // For Julia, we treat (cr, ci) as the *starting point*
                // and use (jr, ji) as the *constant*.
                f->color = julia(cr, ci, f->jr, f->ji);
            }

            my_mlx_pixel_put(&f->img, x, y, f->color);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(f->mlx, f->mlx_win, f->img.img, 0, 0);
}




// Mouse hook to zoom
int	mouse_hook(int button, int x, int y, void *param)
{
	t_fractol *f = (t_fractol *)param;
	double scale;

	if (button == 4)
		scale = 0.90; // Zoom in (10%)
	else if (button == 5)
		scale = 1.10; // Zoom out (10%)
	else
		return (0);

	double range_x = f->x_max - f->x_min;
	double range_y = f->y_max - f->y_min;

	double mx = f->x_min + (x / (double)WIDTH) * range_x;
	double my = f->y_min + (y / (double)HEIGHT) * range_y;

	f->x_min = mx - (mx - f->x_min) * scale;
	f->x_max = f->x_min + range_x * scale;
	f->y_min = my - (my - f->y_min) * scale;
	f->y_max = f->y_min + range_y * scale;

	if (scale < 1.0 && f->max_iter < 300)
		f->max_iter += 5;
	else if (scale > 1.0 && f->max_iter > 50)
		f->max_iter -= 5;

	rander_fractol(f);
	return (0);
}

int key_hook(int keycode, t_fractol *f)
{
    // On Linux, ESC is 65307. On macOS, it's 53.
    if (keycode == 65307)
    {
        mlx_destroy_window(f->mlx, f->mlx_win);
        exit(0);
    }
    return (0);
}


int close_window(t_fractol *f)
{
    // Clean up your resources if needed.
    // E.g., free memory, destroy images, etc.

    mlx_destroy_window(f->mlx, f->mlx_win);
    exit(0); // Exit the program cleanly
    return (0);
}


int	main(int argc , char *argv[])
{
    if (argc > 1)
    {
        t_fractol fractol;
        if (pars(argv , argc , &fractol) == 0)
        {
            ft_printf("Usage: ./fractol Mandelbrot \n       ./fractol Julia <RealPart> <ImagPart>\n");
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
        ft_printf("Usage: ./fractol Mandelbrot \n       ./fractol Julia <RealPart> <ImagPart>\n");
    
    return 0;
}
