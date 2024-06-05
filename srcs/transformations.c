/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 01:57:42 by forrest           #+#    #+#             */
/*   Updated: 2024/05/16 22:44:55 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate_points(t_vars *data)
{
	data->p.y += data->translate_y;
	data->pr.y += data->translate_y;
	data->pd.y += data->translate_y;
	data->p.x += data->translate_x;
	data->pr.x += data->translate_x;
	data->pd.x += data->translate_x;
}

void	altitude(t_vars *data)
{
	data->p.z *= data->altitude_factor;
	data->pr.z *= data->altitude_factor;
	data->pd.z *= data->altitude_factor;
}

void	original_state(int keycode, t_vars *data)
{
	if (keycode == O)
	{
		data->rot_x = 50;
		data->rot_y = 0;
		data->rot_z = 45;
		data->translate_x = 0;
		data->translate_y = 0;
		data->altitude_factor = 1.00;
		data->zoom_factor = 1.00;
		print_model(data);
	}
}

void	zoom(t_vars *data)
{
	data->p.x *= data->zoom_factor;
	data->p.y *= data->zoom_factor;
	data->pd.x *= data->zoom_factor;
	data->pd.y *= data->zoom_factor;
	data->pr.x *= data->zoom_factor;
	data->pr.y *= data->zoom_factor;
}

void	transform_points(t_vars *data)
{
	data->p.x -= data->space_shift_center_left;
	data->p.y -= data->space_shift_centre_up;
	data->pd.x -= data->space_shift_center_left;
	data->pd.y -= data->space_shift_centre_up;
	data->pr.x -= data->space_shift_center_left;
	data->pr.y -= data->space_shift_centre_up;
	altitude(data);
	change_color(data);
	rotate_points(data);
	zoom(data);
	translate_points(data);
	data->p.x += data->space_shift_center_left + data->space_shift_right;
	data->p.y += data->space_shift_centre_up + data->space_shift_down;
	data->pd.x += data->space_shift_center_left + data->space_shift_right;
	data->pd.y += data->space_shift_centre_up + data->space_shift_down;
	data->pr.x += data->space_shift_center_left + data->space_shift_right;
	data->pr.y += data->space_shift_centre_up + data->space_shift_down;
}
