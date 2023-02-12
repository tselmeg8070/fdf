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
	*(unsigned int*)dst = color;
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_map	map;
	int		**cord;

	if (argc == 2)
	{
		ft_map_from_file(argv[1], &map);
		for (int i = 0; i < map.row; i++)
		{
			for (int j = 0; j < map.col; j++)
			{
				printf("%d ", map.map[i * map.row + j]);
			}
			printf("\n");
		}
		free(map.map);
		// mlx = mlx_init();
		// mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
		// img.img = mlx_new_image(mlx, 1920, 1080);
		// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		// 	&img.line_length, &img.endian);
		// ft_mlx_pixel_put(&img, 5, 5, 0x00FFFFFF);
		// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		// mlx_loop(mlx);
	}
}
