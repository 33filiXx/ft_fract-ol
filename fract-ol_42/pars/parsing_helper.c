/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:52:06 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/04/10 15:53:45 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nrc/fractol.h"

void	check_ponit(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[i][j] == '-' || str[i][j] == '+')
		j++;
	if (str[i][j] == '.')
	{
		write(2, "Usage: ./fractol mandelbrot\n.", 30);
		write(2, "/fractol julia <RealPart> <ImagPart>\n", 38);
		write(2, "/fractol burningship\n", 22);
		exit(1);
	}
}

int	check_p_m(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			return (1);
		i++;
	}
	return (0);
}
