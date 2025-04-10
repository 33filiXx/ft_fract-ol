/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-mjiy <wel-mjiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:17:33 by wel-mjiy          #+#    #+#             */
/*   Updated: 2025/04/10 09:26:32 by wel-mjiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nrc/fractol.h"

int	burningship(double cr, double ci, int max_iter)
{
	double	zr;
	double	zi;
	int		i;
	double	tmp;

	zr = 0.0;
	zi = 0.0;
	i = 0;
	while (i < max_iter)
	{
		tmp = zr * zr - zi * zi + cr;
		zi = fabs(2.0 * zr * zi + ci);
		zr = fabs(tmp);
		if ((zr * zr + zi * zi) > 4.0)
			break ;
		i++;
	}
	if (i == max_iter)
		return (0x000000);
	else
		return (get_color(i, max_iter));
}
