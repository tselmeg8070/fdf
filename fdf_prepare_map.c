/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_prepare_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:40:30 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/02/25 20:31:21 by tadiyamu         ###   ########.fr       */
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
	int	i;

	map->map = malloc(sizeof(int) * map->row * map->col);
	if (!map->map)
		ft_error_gen();
	i = 0;
	while (i < map->row * map->col)
		map->map[i++] = 0;
	map->points = malloc(sizeof(t_point) * map->row * map->col);
	if (!map->points)
	{
		free(map->map);
		ft_error_gen();
	}
	map->tile_width = TILE_WIDTH;
	map->max = 1;
	map->min = 1;
}

void	ft_map_bottom_up(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->row * map->col)
	{
		if (map->map[i] < map->min)
			map->min = map->map[i];
		i++;
	}
	i = 0;
	while (i < map->row * map->col)
	{
		map->map[i] -= map->min;
		if (map->map[i] > map->max)
			map->max = map->map[i];
		i++;
	}
}

void	ft_map_from_file(char *file, t_map *map)
{
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
	// ft_map_bottom_up(map);
	if (map->tile_width > 540 / map->col)
		map->tile_width = 540 / map->col;
	if (map->tile_width < 4)
		map->tile_width = 2;
	free(content);
}
