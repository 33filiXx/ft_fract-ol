#include "../nrc/fractol.h"
int	mouse_hook(int button, int x, int y, void *param)
{
	t_fractol	*f = (t_fractol *)param;
	double		scale;

	if (button == 4)          // scroll up  → zoom in 15 %
		scale = 0.85;
	else if (button == 5)     // scroll down→ zoom out 15 %
		scale = 1.15;
	else
		return (0);

	double range_x = f->x_max - f->x_min;
	double range_y = f->y_max - f->y_min;

	double mx = f->x_min + (x * range_x) * (1.0 / WIDTH);
	double my = f->y_min + (y * range_y) * (1.0 / HEIGHT);

	f->x_min = mx - (mx - f->x_min) * scale;
	f->x_max = f->x_min + range_x * scale;
	f->y_min = my - (my - f->y_min) * scale;
	f->y_max = f->y_min + range_y * scale;

	/* dynamic detail but capped so it never explodes */
	if (scale < 1.0 && f->max_iter < 50)
		f->max_iter += 3;
	else if (scale > 1.0 && f->max_iter > 30)
		f->max_iter -= 3;

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