/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:40:30 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/02/12 16:40:31 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_split_free(char ***res)
{
	int	i;

	i = 0;
	while ((*res) && (*res)[i] != 0)
	{
		free((*res)[i]);
		i++;
	}
	if (*res)
		free(*res);
}

void	ft_error_gen(void)
{
	write(2, "Error\n", 7);
	exit(1);
}

void	ft_malloc_map(t_map *map)
{
	map->map = malloc(sizeof(int) * map->row * map->col);
	if (!map->map)
		ft_error_gen();
	map->points = malloc(sizeof(t_point) * map->row * map->col);
	if (!map->points)
	{
		free(map->map);
		ft_error_gen();
	}
	map->max = 0;
	map->min = 0;
}

void	ft_map_bottom_up(t_map *map)
{
	int	i;
	int	min;

	min = 0;
	i = 0;
	while (i < map->row * map->col)
	{
		if (map->map[i] < min)
			min = map->map[i];
		i++;
	}
	i = 0;
	while (i < map->row * map->col)
	{
		map->map[i] += (-1) * min;
		i++;
	}
}

void	ft_map_from_file(char *file, t_map *map)
{
	int		i;
	char	*content;

	content = 0;
	if (!ft_cnt_line(file, map, &content))
		ft_error_gen();
	ft_malloc_map(map);
	if (!ft_file_to_cord(content, map))
	{
		free(map->map);
		free(content);
		ft_error_gen();
	}
	ft_map_bottom_up(map);
	free(content);
}
