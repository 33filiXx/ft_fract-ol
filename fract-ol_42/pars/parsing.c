# include "../nrc/fractol.h"


int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}



int pars(char **str)
{
	int check = 0;
    if (ft_strcmp(str[1] , "Mandelbrot") == 0 && str[2] == NULL)
		check = 1;
	if (ft_strcmp(str[1] , "Julia") == 0)
		check = 1;
	return check;
}