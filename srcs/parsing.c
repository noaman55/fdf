/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noudrib <noudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:07:16 by noudrib           #+#    #+#             */
/*   Updated: 2024/05/16 18:32:43 by noudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"   

void	fill_point(int i, int j, char *points, t_vars *data)
{
	char	**point;

	point = ft_split(points, ',');
	data->map[j][i].x = i;
	data->map[j][i].y = j;
	data->map[j][i].z = ft_atoi(point[0]);
	data->map[j][i].color = hex_to_int(point[1]);
	data->map[j][i].last_point = 0;
	free_tab((void **)point);
}

void	fill_map(t_list **head_lines, t_vars *data)
{
	t_list	*line_ptr;
	char	**points;
	int		i;
	int		j;
	int		line_size;	

	j = 0;
	line_ptr = *head_lines;
	while (line_ptr)
	{
		points = ft_split(line_ptr -> content, ' ');
		line_size = array_size(points);
		if (ft_strcmp(points[line_size - 1], "\n") == 0)
			line_size--;
		data->map[j] = (t_point *) malloc(sizeof(t_point) * (line_size + 1));
		if (data->map[j] == NULL)
			return ;
		i = -1;
		while (++i < line_size)
			fill_point(i, j, points[i], data);
		free_tab((void **)points);
		data->map[j++][i].last_point = -1;
		line_ptr = line_ptr -> next;
	}
	ft_lstclear(head_lines, &free);
}

int	line_length(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n' && (str[i + 1] == ' '
				|| str[i + 1] == '\n' || str[i + 1] == '\0'))
			len++;
		i++;
	}
	return (len);
}

void	read_map2(int fd, char *line, t_vars *data)
{
	int		line_len;
	t_list	*head_lines;

	head_lines = NULL;
	data->map_lines = 0;
	line_len = line_length(line);
	while (line)
	{
		ft_lstadd_back(&head_lines, ft_lstnew(line));
		line = get_next_line(fd);
		if (line != NULL && line_len != line_length(line))
		{
			free(line);
			ft_lstclear(&head_lines, &free);
			exit((ft_printf("Found wrong line length. Exiting.\n"), 1));
		}
		data->map_lines++;
	}
	data->map = (t_point **) malloc(sizeof(t_point *) * (data->map_lines + 1));
	if (data->map == NULL)
		exit ((ft_lstclear(&head_lines, &free),
				ft_printf("malloc failed\n"), 1));
	data->map[data->map_lines] = NULL;
	data->map_colomns = line_len;
	fill_map(&head_lines, data);
}

void	read_map(char *path, t_vars *data)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit((ft_printf("an error occurred while parsing the map\n"), 1));
	line = get_next_line(fd);
	if (line == NULL || ft_strcmp("\n", line) == 0)
		exit((free(line), ft_printf("No data found.\n"), 1));
	read_map2(fd, line, data);
}
