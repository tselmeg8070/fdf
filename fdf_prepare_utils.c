/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_prepare_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:13:06 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/02/25 20:31:28 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_cnt_split(char *line)
{
	int		c;
	int		i;
	char	**split;

	i = 0;
	c = 0;
	split = ft_split(line, ' ');
	while (split && split[i] != NULL)
	{
		if (ft_strncmp(split[i], "\n", 1) != 0)
			c++;
		free(split[i]);
		i++;
	}
	if (split)
		free(split);
	return (c);
}

void	ft_cnt_line_util(char **temp, char **line)
{
	free(*temp);
	free(*line);
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
			if (c == 1)
				map->col = ft_cnt_split(line);
			temp = *content;
			*content = ft_strjoin(*content, line);
			ft_cnt_line_util(&temp, &line);
		}
	}
	close(fd);
	map->row = c;
	return (1);
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
		if (c >= map->col)
			res = 0;
		else
			ft_split_to_cord(map, row, c, split[c]);
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
