/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_points_cal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 20:30:49 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/02/25 20:30:52 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_cal_x(int r, int c, t_map *map)
{
	int	x;

	x = 1080 / 2 + (r - c) * map->tile_width;
	return (x);
}

int	ft_cal_y(int r, int c, t_map *map)
{
	int	y;

	y = 1080 / 2 + (r + c) * map->tile_width / 2;
	y -= map->map[r * map->col + c] * map->tile_width * 1.4;
	return (y);
}

void	ft_topping(t_map *map)
{
	int	r;
	int	c;

	r = 0;
	while (r < map->row)
	{
		c = 0;
		while (c < map->col)
		{
			map->points[map->col * r + c].x -= map->min;
			map->points[map->col * r + c].y -= map->min;
			c++;
		}
		r++;
	}
}

void	ft_calculate_points(t_map *map)
{
	int	r;
	int	c;

	r = 0;
	while (r < map->row)
	{
		c = 0;
		while (c < map->col)
		{
			map->points[map->col * r + c].x = ft_cal_x(r, c, map);
			if (map->points[map->col * r + c].x < map->min)
				map->min = map->points[map->col * r + c].x;
			map->points[map->col * r + c].y = ft_cal_y(r, c, map);
			if (map->points[map->col * r + c].y < map->min)
				map->min = map->points[map->col * r + c].y;
			map->points[map->col * r + c].rend = 0;
			c++;
		}
		r++;
	}
	ft_topping(map);
}
