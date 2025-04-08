#include "../nrc/fractol.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
int	skip(char *s, long *sign)
{
	int	i;

	i = 0;
	while ((s[i] && (s[i] >= 9 && s[i] <= 13)) || s[i] == 32)
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			*sign *= -1;
		i++;
	}
	return (i);
}

double	ft_atof(char *s)
{
	long(int_part), (i), (sign);
	double(pow), (fracti_part);
	int_part = 0;
	fracti_part = 0;
	sign = 1;
	pow = 1;
	i = skip(s, &sign);
	if (!s[i] || !(s[i] >= 48 && s[i] <= 57))
		exit(EXIT_FAILURE);
	while (s[i] && s[i] != '.')
		int_part *= 10 + (s[i++] - 48);
	if (s[i] == '.')
		i++;
	while (s[i])
	{
		pow /= 10;
		fracti_part = fracti_part + (s[i++] - 48) * pow;
	}
	return ((int_part + fracti_part) * sign);
}

int	pars(char **str, int argc, t_fractol *f)
{
	int check = 0;
	if (ft_strcmp(str[1], "mandelbrot") == 0 && str[2] == NULL)
	{
		check = 1;
		f->fractal_type = 1;
	}
	if (ft_strcmp(str[1], "julia") == 0 && argc == 4)
	{
		check = 1;
		f->fractal_type = 2;
		f->jr = ft_atof(str[2]);
		f->ji = ft_atof(str[3]);
	}
	return (check);
}