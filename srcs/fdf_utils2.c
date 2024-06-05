/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forrest <forrest@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:54:30 by noudrib           #+#    #+#             */
/*   Updated: 2024/06/05 00:00:00 by forrest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

void	close_win(int keycode, t_vars *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(data->mlx, data->img.img);
		mlx_destroy_window(data->mlx, data->win);
		free_tab((void **)data->map);
		exit(0);
	}
}

int	close_win_mouse(t_vars *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	free_tab((void **)data -> map);
	exit(0);
	return (0);
}

void	copy_points(t_vars *data, t_point *original)
{
	data->p.x = original->x;
	data->p.y = original->y;
	data->p.z = original->z;
	data->p.color = original->color;
	data->p.right = original->right;
	data->p.down = original->down;
	if (original->right != NULL)
	{
		data->pr.x = original->right->x;
		data->pr.y = original->right->y;
		data->pr.z = original->right->z;
		data->pr.color = original->right->color;
	}
	if (original->down != NULL)
	{
		data->pd.x = original->down->x;
		data->pd.y = original->down->y;
		data->pd.z = original->down->z;
		data->pd.color = original->down->color;
	}
}

void	configure_keys(int keycode, t_vars *data)
{
	if (keycode == W)
		data->rot_x += 2;
	else if (keycode == Q)
		data->rot_x -= 2;
	else if (keycode == S)
		data->rot_y += 2;
	else if (keycode == A)
		data->rot_y -= 2;
	else if (keycode == X)
		data->rot_z += 2;
	else if (keycode == Z)
		data->rot_z -= 2;
	else if (keycode == UP)
		data->translate_y -= 20;
	else if (keycode == DOWN)
		data->translate_y += 20;
	else if (keycode == RIGHT)
		data->translate_x += 20;
	else if (keycode == LEFT)
		data->translate_x -= 20;
	else if (keycode == E)
		data->altitude_factor -= 0.1;
	else if (keycode == R)
		data->altitude_factor += 0.1;
}

void	configure_keys2(int keycode, t_vars *data)
{
	if (keycode == C)
		data->switch_color++;
	else if (keycode == PARALLEL_PROJ)
	{
		data->rot_x = 0;
		data->rot_y = 0;
		data->rot_z = 0;
		data->translate_x = 0;
		data->translate_y = 0;
		data->altitude_factor = 1.00;
		data->zoom_factor = 1.00;
		print_model(data);
	}
}
