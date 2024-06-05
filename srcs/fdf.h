/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forrest <forrest@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:01:23 by noudrib           #+#    #+#             */
/*   Updated: 2024/06/05 00:04:58 by forrest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include <math.h>
#define WIDTH 1920
#define HEIGHT 1080

// #define Q 12
// #define W 13
// #define A 0
// #define S 1
// #define Z 6
// #define X 7
// #define O 31
// #define E 14
// #define R 15
// #define D 2
// #define F 3
// #define PARALLEL_PROJ 35
// #define C 8
// #define LEFT 123
// #define RIGHT 124
// #define UP 126
// #define DOWN 125
// #define SCROLLUP 5
// #define SCROLLDOWN 4
// #define ESC 53

#define PI 3.14159265359

#define Q 113
#define W 119
#define A 97
#define S 115
#define Z 122
#define X 120
#define O 111
#define E 101
#define R 114
#define D 100
#define F 102
#define PARALLEL_PROJ 112
#define C 99
#define LEFT 65361
#define RIGHT 65363
#define UP 65362
#define DOWN 65364
#define SCROLLUP 4
#define SCROLLDOWN 5
#define ESC 65307

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
	int				last_point;
	struct s_point	*right;
	struct s_point	*down;
}				t_point;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_point	**map;
	t_data	img;
	int		map_lines;
	int		map_colomns;
	int		space_gap;
	int		space_shift_right;
	int		space_shift_down;
	int		space_shift_center_left;
	int		space_shift_centre_up;
	int		rot_x;
	int		rot_y;
	int		rot_z;
	int		translate_y;
	int		translate_x;
	float	altitude_factor;
	float	zoom_factor;
	t_point	p;
	t_point	pd;
	t_point	pr;
	int		key;
	int		mouse_button;
	int		mouse_x;
	int		mouse_y;
	int		alt_min;
	int		alt_max;
	int		switch_color;
}				t_vars;

//t_point	**read_map(char *path, t_vars *data);
int		array_size(char **arr);
void	read_map(char *path, t_vars *data);
int		hex_to_int(char *str);
void	free_tab(void **tab);
void	draw_line(t_point point1, t_point point2, t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	rotate_x(t_point *point, t_vars *data);
void	rotate_y(t_point *point, t_vars *data);
void	rotate_z(t_point *point, t_vars *data);
void	rotate_points(t_vars *data);
void	translate_points(t_vars *data);
void	mlx_hook_event(t_vars *data);
void	copy_points(t_vars *data, t_point *original);
void	transform_points(t_vars *data);
void	original_state(int keycode, t_vars *data);
void	reset_image(t_vars *data);
void	print_lines(t_vars *data);
void	zoom(t_vars *data);
void	close_win(int keycode, t_vars *data);
int		close_win_mouse(t_vars *data);
int		create_trgb(int t, int r, int g, int b);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
void	print_manual(t_vars *data);
void	print_model(t_vars *data);
void	configure_keys(int keycode, t_vars *data);
void	configure_keys2(int keycode, t_vars *data);
void	color_range(t_vars *data);
void	change_color(t_vars *data);
void	change_color_point(t_point *p, t_vars *data);
