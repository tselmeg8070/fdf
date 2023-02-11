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
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "get_next_line.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_map {
	int		**map;
	int		row;
	int		col;
}	t_map;

int	ft_file_to_cord(char *file, t_map *map);

int	ft_cnt_line(char *file, t_map *map);

#endif
