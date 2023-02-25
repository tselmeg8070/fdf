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
#include <X11/X.h>
#include <X11/keysym.h>

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
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
			if (map->points[map->col * r + c].x > map->max)
				map->max = map->points[map->col * r + c].x;
			if (map->points[map->col * r + c].y > map->max)
				map->max = map->points[map->col * r + c].y;
			c++;
		}
		r++;
	}
}

int	handle_input(int keysym, t_vars *vars)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = 0;
	}
	return (0);
}

int	handle_cross(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	vars->win = 0;
	return (0);
}

/* This function needs to exist, but it is useless for the moment */
int	handle_no_event(void *data)
{
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_data	img;
	t_map	map;

	if (argc == 2)
	{
		ft_map_from_file(argv[1], &map);
		ft_calculate_points(&map);
		ft_calculate_window_size(&map);
		vars.mlx = mlx_init();
		vars.win = mlx_new_window(vars.mlx, map.max, map.max, argv[1]);
		img.img = mlx_new_image(vars.mlx, map.max, map.max);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
		ft_connect_points(0, 0, &map, &img);
		mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
		mlx_loop_hook(vars.mlx, &handle_no_event, &vars);
		mlx_key_hook(vars.win, &handle_input, &vars);
		mlx_hook(vars.win, 17, 1L<<0, &handle_cross, &vars);
		mlx_loop(vars.mlx);
		mlx_destroy_image(vars.mlx, img.img);
		mlx_destroy_display(vars.mlx);
		free(vars.mlx);
		free(map.map);
		free(map.points);
	}
}
