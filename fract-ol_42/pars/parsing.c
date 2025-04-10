/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:21:05 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/04/10 15:54:36 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	long (int_part), (i), (sign);
	double (pow), (fracti_part);
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

int	check_if_digit(char **str)
{
	int (i), (counterm), (counterpl), (counterp), (j);
	i = 0;
	check_ponit(str);
	while (str[i])
	{
		counterp = 0;
		counterpl = 0;
		counterm = 0;
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '.')
				counterp++;
			if (str[i][j] == '+')
				counterpl++;
			if (str[i][j] == '-')
				counterm++;
			if (ft_isdigit(str[i][j]) == 0 || counterp > 1 || counterm > 1
				|| counterpl > 1 || check_p_m(str[i]) == 1)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	pars(char **str, int argc, t_fractol *f)
{
	int	check;

	check = 0;
	f->fractal_type = 1;
	if (ft_strcmp(str[1], "mandelbrot") == 0 && str[2] == NULL)
		check = 1;
	else if (ft_strcmp(str[1], "julia") == 0 && argc == 4)
	{
		if (check_if_digit(str + 2) == 1)
		{
			check = 1;
			f->fractal_type = 2;
			f->jr = ft_atof(str[2]);
			f->ji = ft_atof(str[3]);
		}
		else
			return (check);
	}
	else if (ft_strcmp(str[1], "burningship") == 0 && str[2] == NULL)
	{
		check = 1;
		f->fractal_type = 3;
	}
	return (check);
}
