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
	while (split && split[c])
	{
		free(split[c]);
		c++;
	}
	if (split)
		free(split);
	return (c);
}

int	ft_cnt_line(char *file, t_map *map)
{
	int		fd;
	char	*line;
	int		c;

	c = 0;
	fd = open(file, O_RDONLY);
	line = "";
	if (fd < 0)
		return (-1);
	while (line)
	{
		line = get_next_line(fd);
		if (line)
			c++;
		if (line && c == 1)
			map->col = ft_cnt_split(line);
		if (line)
			free(line);
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
		map->map[row][c] = ft_atoi(split[c]);
		res = ft_check_val(split[c], map->map[row][c]);
		c++;
	}
	c = 0;
	while (split && split[c])
	{
		free(split[c]);
		c++;
	}
	if (split)
		free(split);
	return (res);
}

int	ft_file_to_cord(char *file, t_map *map)
{
	int		size;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = "";
	size = 0;
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			if (!ft_assign_split(map, line, size))
			{
				size++;
				close(fd);
				free(line);
				return (0);
			}
			free(line);
		}
	}
	close(fd);
	return (1);
}
