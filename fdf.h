/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:25:24 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/02/11 17:25:25 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "get_next_line.h"

# define TILE_WIDTH 20
# define TILE_HEIGHT 10

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_point {
	int	x;
	int	y;
	int	color;
	int	rend;
}	t_point;

typedef struct s_map {
	int		*map;
	t_point	*points;
	int		row;
	int		col;
	int		min;
	int		max;
	int		tile_width;
	int		tile_height;
}	t_map;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	t_data	img;
}	t_vars;

void	ft_split_free(char ***res);

void	ft_error_gen(void);

int		ft_file_to_cord(char *file, t_map *map);

void	ft_split_to_cord(t_map *map, int r, int c, char *split);

int		ft_cnt_line(char *file, t_map *map, char **content);

void	ft_malloc_map(t_map *map);

void	ft_map_from_file(char *file, t_map *map);

int		ft_cal_x(int r, int c, t_map *map);

int		ft_cal_y(int r, int c, t_map *map);

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);

void	ft_calculate_points(t_map *map);

void	ft_connect_points(int r, int c, t_map *map, t_data *img);

int		handle_input(int keysym, t_vars *vars);

int		handle_cross(t_vars *vars);

int		handle_no_event(void);

#endif
