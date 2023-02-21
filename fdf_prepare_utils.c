/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_prepare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:13:06 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/02/11 17:13:08 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_cnt_split(char *line)
{
	int		c;
	char	**split;

	c = 0;
	split = ft_split(line, ' ');
	while (split && split[c] && ft_strlen(split[c]))
	{
		free(split[c]);
		c++;
	}
	if (split)
		free(split);
	return (c - 1);
}

int	ft_cnt_line(char *file, t_map *map, char **content)
{
	int		fd;
	char	*line;
	char	*temp;
	int		c;

	c = 0;
	fd = open(file, O_RDONLY);
	line = "";
	if (fd < 0)
		return (0);
	while (line)
	{
		line = get_next_line(fd);
		if (line && ++c)
		{
			map->col = ft_cnt_split(line);
			temp = *content;
			*content = ft_strjoin(*content, line);
			free(temp);
			free(line);
		}
	}
	close(fd);
	map->row = c;
	return (1);
}

int	ft_check_val(char *str, int val)
{
	int	dig;

	dig = 0;
	if (val < 0)
		dig++;
	if (val == 0 && ft_strncmp(str, "0", 1) != 0)
		return (0);
	if (val == 0)
		dig = 1;
	while (val != 0)
	{
		dig++;
		val /= 10;
	}
	if (dig == (int) ft_strlen(str))
		return (1);
	return (0);
}

int	ft_assign_split(t_map *map, char *line, int row)
{
	char	**split;
	int		c;
	int		res;

	c = 0;
	res = 1;
	split = ft_split(line, ' ');
	while (split && split[c] && res)
	{
		if (c > map->col)
			res = 0;
		else
		{
			map->map[(row) * map->col + (map->col - 1) - c] = ft_atoi(split[c]);
			res = ft_check_val(split[c], map->map[(row) * map->col + (map->col - 1) - c]);
		}
		c++;
	}
	ft_split_free(&split);
	return (res);
}

int	ft_file_to_cord(char *content, t_map *map)
{
	int		size;
	char	**lines;

	lines = ft_split(content, '\n');
	if (lines == NULL)
		return (0);
	size = 0;
	while (lines[size] != NULL)
	{
		if (ft_assign_split(map, lines[size], size))
			size++;
		else
		{
			ft_split_free(&lines);
			return (0);
		}
	}
	ft_split_free(&lines);
	return (1);
}
