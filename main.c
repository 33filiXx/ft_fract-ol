#include "minilibx-linux/mlx.h"
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void drowcircul(int h , int k , t_data *img)
{
    int radius = 100;
    int x = 0;
    while (x < 1920)
    {
        int y = 0;
        while (y < 1080)
        {
            if (((x - h) * (x -h)) + ((y - k) * (y - k)) <= (radius * radius))
                my_mlx_pixel_put(img , x , y , 0xffffff);
            y++;
        }
        x++;
    }
    
}


int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    drowcircul(1920/2 , 1080 , &img);
    // mlx_hook(mlx_win,  e)
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}