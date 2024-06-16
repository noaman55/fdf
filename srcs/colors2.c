/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forrest <forrest@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:05:28 by noudrib           #+#    #+#             */
/*   Updated: 2024/06/16 19:09:07 by forrest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	color_range(t_vars *data)
{
	int		l;
	int		c;

	data->alt_min = data->map[0][0].z * data->altitude_factor;
	data->alt_max = data->map[0][0].z * data->altitude_factor;
	l = 0;
	while (data->map[l])
	{
		c = 0;
		while (data->map[l][c].last_point != -1)
		{
			if (data->alt_min > data->map[l][c].z * data->altitude_factor)
				data->alt_min = data->map[l][c].z * data->altitude_factor;
			if (data->alt_max < data->map[l][c].z * data->altitude_factor)
				data->alt_max = data->map[l][c].z * data->altitude_factor;
			c++;
		}
		l++;
	}
}

void	color_rgb(int color, t_point *p, t_vars *data)
{
	int		red;
	int		gr;
	int		bl;
	float	per;

	if (data->alt_max == data->alt_min)
		per = 0.5;
	else
		per = (float)ft_abs(p->z - data->alt_min)
			/ (float)ft_abs(data->alt_max - data->alt_min);
	red = (1 - per) * get_r(color) + (per) * get_r(0xFFFFFF);
	gr = (1 - per) * get_g(color) + (per) * get_g(0xFFFFFF);
	bl = (1 - per) * get_b(color) + (per) * get_b(0xFFFFFF);
	p->color = create_trgb(0, red, gr, bl);
}

void	change_color_point(t_point *p, t_vars *data)
{
	int		range;

	range = (float)(data->alt_max - data->alt_min) / 4;
	if (p->z == data->alt_min)
		p->color = 0x3333FF;
	else if (p->z >= data->alt_min && p->z < data->alt_min + range)
		p->color = 0x3333FF;
	else if (p->z >= data->alt_min + range && p->z < data->alt_min + 2 * range)
		p->color = 0x009900;
	else if (p->z >= data->alt_min + 2 * range
		&& p->z < data->alt_min + 3 * range)
		p->color = 0xFF0000;
	else if (p->z >= data->alt_min + 3 * range)
		p->color = 0xFFFFFF;
}

void	change_color(t_vars *data)
{
	int	color;

	if (data->switch_color % 5 == 1)
	{
		change_color_point(&data->p, data);
		change_color_point(&data->pr, data);
		change_color_point(&data->pd, data);
		return ;
	}
	else if (data->switch_color % 5 == 2)
		color = 0xFF0000;
	else if (data->switch_color % 5 == 3)
		color = 0x00FF00;
	else if (data->switch_color % 5 == 4)
		color = 0x0000FF;
	else
		return ;
	color_rgb(color, &data->p, data);
	color_rgb(color, &data->pr, data);
	color_rgb(color, &data->pd, data);
}
