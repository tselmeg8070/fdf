/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_connect_points.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:41:08 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/02/27 13:41:09 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_cal_inc(int point, int dest)
{
	if (point < dest)
		return (1);
	return (-1);
}

void	ft_connect_high(t_point s, t_point e, t_data *img)
{
	int	d[2];
	int	delta;

	d[0] = e.x - s.x;
	d[1] = e.y - s.y;
	d[0] = abs(d[0]);
	delta = 2 * d[0] - d[1];
	while (s.y != e.y)
	{
		ft_mlx_pixel_put(img, s.x, s.y, s.color);
		if (delta > 0)
		{
			s.x += ft_cal_inc(s.x, e.x);
			delta = delta + (2 * (d[0] - d[1]));
		}
		else
			delta = delta + 2 * d[0];
		s.y += ft_cal_inc(s.y, e.y);
	}
	ft_mlx_pixel_put(img, s.x, s.y, s.color);
}

void	ft_connect_low(t_point s, t_point e, t_data *img)
{
	int	d[2];
	int	delta;

	d[0] = e.x - s.x;
	d[1] = e.y - s.y;
	d[1] = abs(d[1]);
	delta = 2 * d[1] - d[0];
	while (s.x != e.x)
	{
		ft_mlx_pixel_put(img, s.x, s.y, s.color);
		if (delta > 0)
		{
			s.y += ft_cal_inc(s.y, e.y);
			delta = delta + (2 * (d[1] - d[0]));
		}
		else
			delta = delta + 2 * d[1];
		s.x += ft_cal_inc(s.x, e.x);
	}
	ft_mlx_pixel_put(img, s.x, s.y, s.color);
}

void	ft_connect(t_point *s, t_point *e, t_data *img)
{
	if (abs(e->y - s->y) < abs(e->x - s->x))
	{
		if (s->x > e->x)
			ft_connect_low(*e, *s, img);
		else
			ft_connect_low(*s, *e, img);
	}
	else
	{
		if (s->y > e->y)
			ft_connect_high(*e, *s, img);
		else
			ft_connect_high(*s, *e, img);
	}
}

void	ft_connect_points(int r, int c, t_map *map, t_data *img)
{
	while (r < map->row)
	{
		c = 0;
		while (c < map->col)
		{
			if (r - 1 >= 0)
				ft_connect(&(map->points[r * map->col + c]),
					&(map->points[(r - 1) * map->col + c]), img);
			if (c - 1 >= 0)
				ft_connect(&(map->points[r * map->col + c]),
					&(map->points[r * map->col + (c - 1)]), img);
			c++;
		}
		r++;
	}
}

// if (r + 1 >= map->row || c + 1 >= map->col)
// 	return ;
// if (map->points[r * map->col + c].rend)
// 	return ;
// map->points[r * map->col + c].rend = 1;
// ft_connect_points(r + 1, c, map, img);
// ft_connect_points(r, c + 1, map, img);
