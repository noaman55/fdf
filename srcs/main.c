/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:05:57 by noudrib           #+#    #+#             */
/*   Updated: 2024/05/16 22:45:30 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

void	calcul_spaces(t_vars *data)
{
	if (WIDTH / data->map_colomns < HEIGHT / data->map_lines)
		data->space_gap = WIDTH / (data->map_colomns + 6);
	else
		data->space_gap = HEIGHT / (data->map_lines + 6);
	data->space_shift_right = (WIDTH - data->space_gap
			* (data->map_colomns - 1)) / 2;
	data->space_shift_down = (HEIGHT - data->space_gap
			* (data->map_lines - 1)) / 2;
	data->space_shift_center_left = data->space_gap
		* (data->map_colomns - 1) / 2;
	data->space_shift_centre_up = data->space_gap
		* (data->map_lines - 1) / 2;
}

void	map_homothety(t_vars *data)
{
	int		l;
	int		c;

	l = 0;
	while (data->map[l])
	{
		c = 0;
		while (data->map[l][c].last_point != -1)
		{
			data->map[l][c].x *= data->space_gap;
			data->map[l][c].y *= data->space_gap;
			data->map[l][c].z *= 5;
			if (data->map[l][c + 1].last_point != -1)
				data->map[l][c].right = &data->map[l][c + 1];
			else
				data->map[l][c].right = NULL;
			if (data->map[l + 1] != NULL)
				data->map[l][c].down = &data->map[l + 1][c];
			else
				data->map[l][c].down = NULL;
			c++;
		}
		l++;
	}
}

void	print_manual(t_vars *data)
{
	mlx_string_put(data->mlx, data->win, 20, 10, 0xFFFFFF, "Altitude  + : R");
	mlx_string_put(data->mlx, data->win, 20, 30, 0xFFFFFF, "Altitude  - : E");
	mlx_string_put(data->mlx, data->win, 20, 50, 0xFFFFFF, "Rotation  X : Q W");
	mlx_string_put(data->mlx, data->win, 20, 70, 0xFFFFFF, "Rotation  Y : A S");
	mlx_string_put(data->mlx, data->win, 20, 90, 0xFFFFFF, "Rotation  Z : Z X");
	mlx_string_put(data->mlx, data->win, 20, 110, 0xFFFFFF,
		"Translation : Arrows and mouse");
	mlx_string_put(data->mlx, data->win, 20, 130, 0xFFFFFF,
		"Zoom        : Scroll");
	mlx_string_put(data->mlx, data->win, 20, 150, 0xFFFFFF,
		"Isometric Projection : O");
	mlx_string_put(data->mlx, data->win, 20, 170, 0xFFFFFF,
		"Parallel Projection  : P");
}

void	fdf_init(t_vars *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		exit (1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "FDF");
	if (data->win == NULL)
		exit ((mlx_destroy_display(data->mlx), free(data->mlx), 1));
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img.img == NULL)
		exit ((mlx_destroy_window(data->mlx, data->win),
				mlx_destroy_display(data->mlx), free(data->mlx), 1));
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	data->rot_x = 50;
	data->rot_y = 0;
	data->rot_z = 45;
	data->translate_x = 0;
	data->translate_y = 0;
	data->mouse_button = 0;
	data->zoom_factor = 1.00;
	data->altitude_factor = 1.00;
	data->switch_color = 0;
}

int	main(int argc, char **argv)
{
	t_vars	data;

	if (argc != 2)
		return (0);
	fdf_init(&data);
	read_map(argv[1], &data);
	calcul_spaces(&data);
	map_homothety(&data);
	color_range(&data);
	print_model(&data);
	mlx_hook_event(&data);
	mlx_loop(data.mlx);
	return (0);
}
