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
		ft_error_gen();
	}
	free(content);
}
