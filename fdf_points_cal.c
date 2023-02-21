#include "fdf.h"

int		ft_cal_x(int r, int c, t_map *map)
{
	int	x;

	// x = (-1) * map->min + 50 + (r - c) * map->tile_width;
	x = 1080 / 2 + (r - c) * map->tile_width;
	// x = (r - c) * TILE_WIDTH;
	return (x);
}

int		ft_cal_y(int r, int c, t_map *map)
{
	int	y;

	// y = map->max + (r + c) * map->tile_width / 2;
	// y = 1080 - (r + c) * map->tile_width / 2;
	y = 1080 / 2 + (r + c) * map->tile_width / 2;
	// y = (r + c) * TILE_HEIGHT;
	y -= map->map[r * map->col + c] * map->tile_width * 1.4;
	return (y);
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
