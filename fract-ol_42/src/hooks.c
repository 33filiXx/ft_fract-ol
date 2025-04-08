#include "../nrc/fractol.h"

int	mouse_hook(int button, int x, int y, void *param)
{
	t_fractol	*f;

	double(scale), (range_x), (range_y);
	f = (t_fractol *)param;
	if (button == 4)
		scale = 0.85;
	else if (button == 5)
		scale = 1.15;
	else
		return (0);
	range_x = f->x_max - f->x_min;
	range_y = f->y_max - f->y_min;
	f->mx = f->x_min + (x * range_x) * (1.0 / WIDTH);
	f->my = f->y_min + (y * range_y) * (1.0 / HEIGHT);
	f->x_min = f->mx - (f->mx - f->x_min) * scale;
	f->x_max = f->x_min + range_x * scale;
	f->y_min = f->my - (f->my - f->y_min) * scale;
	f->y_max = f->y_min + range_y * scale;
	if (scale < 1.0 && f->max_iter < 50)
		f->max_iter += 3;
	else if (scale > 1.0 && f->max_iter > 30)
		f->max_iter -= 3;
	rander_fractol(f);
	return (0);
}

int	key_hook(int keycode, t_fractol *fractol)
{
	if (keycode == 65307)
		cleanup_and_exit(fractol);
	return (0);
}

int	close_window(t_fractol *fractol)
{
	cleanup_and_exit(fractol);
	return (0);
}