/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 12:30:12 by noudrib           #+#    #+#             */
/*   Updated: 2024/05/16 22:48:10 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	mouse_click(int button, int x, int y, t_vars *data)
{
	data->mouse_button = button;
	data->mouse_x = x;
	data->mouse_y = y;
	if (button == SCROLLDOWN)
	{
		if (data->zoom_factor > 1)
			data->zoom_factor -= 0.10;
		else if (data->zoom_factor == 1)
			return (0);
	}
	else if (button == SCROLLUP)
		data->zoom_factor += 0.10;
	else
		return (0);
	print_model(data);
	return (0);
}

int	mouse_move(int x, int y, t_vars *data)
{
	if (data->mouse_button == 1)
	{
		data->translate_x += (x - data->mouse_x);
		data->translate_y += (y - data->mouse_y);
		data->mouse_x = x;
		data->mouse_y = y;
		print_model(data);
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_vars *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		data->mouse_button = 0;
	return (0);
}

int	keybord_handler(int keycode, t_vars *data)
{
	printf("%d\n", keycode);
	data->key = keycode;
	configure_keys(keycode, data);
	configure_keys2(keycode, data);
	print_model(data);
	original_state(keycode, data);
	close_win(keycode, data);
	return (0);
}

void	mlx_hook_event(t_vars *data)
{
	mlx_hook(data->win, 2, 1L << 0, keybord_handler, data);
	mlx_hook(data->win, 4, 1L << 2, mouse_click, data);
	mlx_hook(data->win, 5, 1L << 3, mouse_release, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->win, 17, 0, close_win_mouse, data);
}
