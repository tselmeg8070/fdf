/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:08:23 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/02/11 16:03:06 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	ft_put_points(t_data *img, t_map *map)
{
	int	r;
	int	c;
	int	*arr;

	r = 0;
	while (r < map->row)
	{
		c = 0;
		while (c < map->col)
		{
			ft_mlx_pixel_put(img, map->points[map->col * r + c].x,
				map->points[map->col * r + c].y, 0x00FFFFFF);
			// ft_mlx_pixel_put(img, 4,
			// 	8, 0x00FFFFFF);
			c++;
		}
		r++;
	}
}

void	ft_calculate_window_size(t_map *map)
{
	int	r;
	int	c;

	r = 0;
	while (r < map->row)
	{
		c = 0;
		while (c < map->col)
		{
			if ((r - c) * TILE_WIDTH > map->max)
				map->max = (r - c) * TILE_WIDTH;
			if ((r + c) * TILE_HEIGHT > map->max)
				map->max = (r + c) * TILE_HEIGHT;
			if ((r - c) * TILE_WIDTH < map->min)
				map->min = (r - c) * TILE_WIDTH;
			if ((r + c) * TILE_HEIGHT < map->min)
				map->min = (r + c) * TILE_HEIGHT;
			c++;
		}
		r++;
	}
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_map	map;

	if (argc == 2)
	{
		ft_map_from_file(argv[1], &map);
		ft_calculate_window_size(&map);
		ft_calculate_points(&map);
		mlx = mlx_init();
		mlx_win = mlx_new_window(mlx, 1900 , 1080, argv[1]);
		img.img = mlx_new_image(mlx, 1900, 1080);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
		// ft_put_points(&img, &map);
		ft_connect_points(0, 0, &map, &img);
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		mlx_loop(mlx);
		free(map.map);
		free(map.points);
	}
}
