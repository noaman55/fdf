/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forrest <forrest@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:01:57 by noudrib           #+#    #+#             */
/*   Updated: 2024/06/16 19:08:09 by forrest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

// int	point_color(int color1, int color2, int x1, int x2, int x)
// {
// 	int		color;
// 	int		red;
// 	int		gr;
// 	int		bl;
// 	float	per;

// 	per = (float)abs(x - x1) / (float)abs(x1 - x2);
// 	red = (1 - per) * get_r(color1) + (per) * get_r(color2);
// 	gr = (1 - per) * get_g(color1) + (per) * get_g(color2);
// 	bl = (1 - per) * get_b(color1) + (per) * get_b(color2);
// 	color = create_trgb(0, red, gr, bl);
// 	return (color);
// }

int	ft_abs(int n)
{
	if (n >= 0)
		return (n);
	return (-n);
}

int	point_color(int color1, int color2, int x2, int x)
{
	int		color;
	int		red;
	int		gr;
	int		bl;
	float	per;

	per = (float)ft_abs(x - 0) / (float)ft_abs(0 - x2);
	red = (1 - per) * get_r(color1) + (per) * get_r(color2);
	gr = (1 - per) * get_g(color1) + (per) * get_g(color2);
	bl = (1 - per) * get_b(color1) + (per) * get_b(color2);
	color = create_trgb(0, red, gr, bl);
	return (color);
}

void	draw_line(t_point point1, t_point point2, t_data *img)
{
	t_dda	var;
	int		i;
	float	x;
	float	y;

	var.dx = point2.x - point1.x;
	var.dy = point2.y - point1.y;
	var.steps = ft_abs(var.dy);
	if (ft_abs(var.dx) > ft_abs(var.dy))
		var.steps = ft_abs(var.dx);
	var.xinc = var.dx / (float) var.steps;
	var.yinc = var.dy / (float) var.steps;
	x = point1.x;
	y = point1.y;
	my_mlx_pixel_put(img, point1.x, point1.y, point1.color);
	i = 0;
	while (i < var.steps)
	{
		x += var.xinc;
		y += var.yinc;
		my_mlx_pixel_put(img, x, y, point_color(point1.color,
				point2.color, var.steps, i++));
	}
}

// void	draw_line(t_point point1, t_point point2, t_data *img)
// {
// 	int		i;
// 	int		dx;
// 	int		dy;
// 	int		steps;
// 	float	xinc;
// 	float	yinc;
// 	float	x;
// 	float	y;

// 	dx = point2.x - point1.x;
// 	dy = point2.y - point1.y;
// 	if (abs(dx) > abs(dy))
// 		steps = abs(dx);
// 	else
// 		steps = abs(dy);
// 	xinc = dx / (float) steps;
// 	yinc = dy / (float) steps;
// 	x = point1.x;
// 	y = point1.y;
// 	my_mlx_pixel_put(img, x, y, point1.color);
// 	i = 0;
// 	while (i < steps)
// 	{
// 		x += xinc;
// 		y += yinc;
// 		my_mlx_pixel_put(img, x, y, point_color(point1.color,
// 			point2.color, 0, steps, i++));
// 	}
// }

void	print_model(t_vars *data)
{
	int	l;
	int	c;

	reset_image(data);
	l = 0;
	color_range(data);
	while (data->map[l])
	{
		c = 0;
		while (data->map[l][c].last_point != -1)
		{
			copy_points(data, &data->map[l][c++]);
			transform_points(data);
			print_lines(data);
		}
		l++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	print_manual(data);
}

// void draw_line(t_point point1, t_point point2, t_data *img)//
	//t_data *img, int x0, int y0, int x1, int y1, int color)
// {
//     int	dx = point2.x - point1.x;
//     int	dy = point2.y - point1.y;;
//     int	sx;
// 	int	sy;
// 	int	err;
// 	int	e2;
//     int i;
//     int max;

//     if (dx > 0)
//         sx = 1;
//     else if (dx < 0)
//         sx = -1;
//     else
//         sx = 0;

//     if (dy > 0)
//         sy = 1;
//     else if (dy < 0)
//         sy = -1;
//     else
//         sy = 0;

//     dx = abs(dx);
//     dy = abs(dy);
//     max = max();
//     i = 0;
//     err = dx - dy;
//     while (point1.x != point2.x || point1.y != point2.y)
//     {
//        //printf("(%d, %d)\n", x0, y0);
//         my_mlx_pixel_put(img, point1.x, point1.y, point_color(point1.color,
							//point2.color, 0, max, i++));
//         e2 = err;
//         if (e2 > -dy) {
//             err -= dy;
//             point1.x += sx;
//         }
//         if (e2 < dx) {
//             err += dx;
//             point1.y += sy;
//         }
//     }
// }

// void	draw_line(t_point point1, t_point point2, t_data *img)
// {
// 	int	dx;
// 	int	dy;
// 	int	sx;
// 	int	sy;
// 	int	err;
// 	int	x;
// 	int	y;

// 	dx = abs(point1.x - point2.x);
// 	dy = abs(point1.y - point2.y);
// 	if (point1.x > point2.x)
// 		sx = -1;
// 	else
// 		sx = 1;
// 	if (point1.y > point2.y)
// 		sy = -1;
// 	else
// 		sy = 1;
// 	if (dx > dy)
// 	{
// 		x= point1.x;
// 		err = dx / 2;
// 		while (point1.x != point2.x)
// 		{
// 			// my_mlx_pixel_put(img, point1.x, point1.y, point1.color);
// 			my_mlx_pixel_put(img, point1.x, point1.y, point_color(point1.color,
							//point2.color, x, point2.x, point1.x));
// 			err -= dy;
// 			if (err < 0)
// 			{
// 				point1.y += sy;
// 				err += dx;
// 			}
// 			point1.x += sx;
// 		}
// 	}
// 	else
// 	{
// 		y = point1.y;
// 		err = dy / 2;
// 		while (point1.y != point2.y)
// 		{
// 			// my_mlx_pixel_put(img, point1.x, point1.y, point2.color);
// 			my_mlx_pixel_put(img, point1.x, point1.y, point_color(point1.color,
							//point2.color, y, point2.y, point1.y));
// 			err -= dx;
// 			if (err < 0)
// 			{
// 				point1.x += sx;
// 				err += dy;
// 			}
// 			point1.y += sy;
// 		}
// 	}
// }

// void bresenham_line(int x0, int y0, int x1, int y1) {
//     int dx;
//     int dy;
//     int sx;
//     int sy;
//     int err;
//     int e2;

// 	dx = abs(x1 - x0);
//     dy = abs(y1 - y0);
//     sx = x0 < x1 ? 1 : -1;
//     sy = y0 < y1 ? 1 : -1;
//     err = dx - dy;
//     while (1) {
//         printf("(%d, %d)\n", x0, y0);
//         if (x0 == x1 && y0 == y1)
//             break;
//         e2 = err * 2;
//         if (e2 > -dy) {
//             err -= dy;
//             x0 += sx;
//         }
//         if (e2 < dx) {
//             err += dx;
//             y0 += sy;
//         }
//     }
// }
