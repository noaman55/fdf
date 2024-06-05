/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:14:31 by noudrib           #+#    #+#             */
/*   Updated: 2024/05/12 10:37:39 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return ;
	dst = data -> addr + (y * data -> line_length + x
			* (data -> bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	char_index(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c || base[i] - 32 == c)
			return (i);
		i++;
	}
	return (0);
}

int	hex_to_int(char *str)
{
	int		i;
	int		num;
	char	*hex;

	if (str == NULL)
		return (0xFFFFFF);
	i = 0;
	num = 0;
	hex = "0123456789abcdef";
	if (ft_strncmp(str, "0x", 2) == 0 || ft_strncmp(str, "0X", 2))
		i = i + 2;
	while (str[i])
		num = num * 16 + char_index(hex, str[i++]);
	return (num);
}

void	print_lines(t_vars *data)
{
	if (data->p.right != NULL)
		draw_line(data->p, data->pr, &data->img);
	if (data->p.down != NULL)
		draw_line(data->p, data->pd, &data->img);
}

void	reset_image(t_vars *data)
{
	int	l;
	int	c;

	l = 0;
	while (l < HEIGHT)
	{
		c = 0;
		while (c < WIDTH)
			my_mlx_pixel_put(&data->img, c++, l, 0);
		l++;
	}
}
