/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:49:57 by noudrib           #+#    #+#             */
/*   Updated: 2024/05/14 22:29:43 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_point *point, t_vars *data)
{
	float	rad;
	int		y;
	int		z;

	rad = (data->rot_x * PI) / 180;
	y = point -> y;
	z = point -> z;
	point -> y = cos(rad) * y - sin(rad) * z;
	point -> z = sin(rad) * y + cos(rad) * z;
}

void	rotate_y(t_point *point, t_vars *data)
{
	float	rad;
	int		x;
	int		z;

	rad = (data->rot_y * PI) / 180;
	x = point -> x;
	z = point -> z;
	point -> x = cos(rad) * x + sin(rad) * z;
	point -> z = -sin(rad) * x + cos(rad) * z;
}

void	rotate_z(t_point *point, t_vars *data)
{
	float	rad;
	int		x;
	int		y;

	rad = (data->rot_z * PI) / 180;
	x = point -> x;
	y = point -> y;
	point -> x = cos(rad) * x - sin(rad) * y;
	point -> y = sin(rad) * x + cos(rad) * y;
}

void	rotate_points(t_vars *data)
{
	rotate_z(&(data->p), data);
	rotate_z(&(data->pr), data);
	rotate_z(&(data->pd), data);
	rotate_x(&(data->p), data);
	rotate_x(&(data->pr), data);
	rotate_x(&(data->pd), data);
	rotate_y(&(data->p), data);
	rotate_y(&(data->pr), data);
	rotate_y(&(data->pd), data);
}
