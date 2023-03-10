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

void	ft_calculate_window_size(t_map *map)
{
	int	r;
	int	c;

	map->width = 5;
	map->height = 5;
	r = 0;
	while (r < map->row)
	{
		c = 0;
		while (c < map->col)
		{
			if (map->points[map->col * r + c].x > map->width)
				map->width = map->points[map->col * r + c].x + 5;
			if (map->points[map->col * r + c].y > map->height)
				map->height = map->points[map->col * r + c].y + 5;
			c++;
		}
		r++;
	}
}

void	ft_final_free(t_map *map, t_vars *vars, t_data *img)
{
	mlx_destroy_window(vars->mlx, vars->win);
	vars->win = 0;
	mlx_destroy_image(vars->mlx, img->img);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free(map->map);
	free(map->points);
}

int	ft_check_ext(char *name)
{
	name = ft_strrchr(name, '.');
	if (ft_strncmp(name, ".fdf\0", 4) == 0)
		return (1);
	ft_error_gen();
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_map	map;

	if (argc == 2 && ft_check_ext(argv[1]))
	{
		ft_map_from_file(argv[1], &map);
		ft_calculate_points(&map);
		ft_calculate_window_size(&map);
		vars.mlx = mlx_init();
		vars.win = mlx_new_window(vars.mlx, map.width, map.height, "FDF");
		vars.img.img = mlx_new_image(vars.mlx, map.width, map.height);
		vars.img.addr = mlx_get_data_addr(vars.img.img,
				&vars.img.bits_per_pixel,
				&vars.img.line_length, &vars.img.endian);
		ft_connect_points(0, 0, &map, &vars.img);
		mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
		mlx_loop_hook(vars.mlx, &handle_no_event, &vars);
		mlx_hook(vars.win, 2, 1L << 0, &handle_input, &vars);
		mlx_hook(vars.win, 17, 1L << 17, &handle_cross, &vars);
		mlx_loop(vars.mlx);
		ft_final_free(&map, &vars, &vars.img);
	}
}
