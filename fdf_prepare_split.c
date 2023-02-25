/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_prepare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:13:06 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/02/11 17:13:08 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_hex_to_dig(char hex)
{
	if (ft_isdigit(hex))
		return (hex - '0');
	else if (hex >= 'a' && hex <= 'f')
		return (10 + (hex - 'a'));
	else if (hex >= 'A' && hex <= 'F')
		return (10 + (hex - 'A'));
	return (-1);
}

int	ft_hex_to_int(char *hex)
{
	int		res;
	int		d;
	double	pw;

	res = 0;
	pw = 0;
	if (hex && ft_strlen(hex) > 2 && hex[0] == '0' && hex[1] == 'x')
	{
		d = ft_strlen(hex) - 1;
		while (d > 1)
		{
			if (ft_hex_to_dig(hex[d]) >= 0)
			{
				res += (int) ft_hex_to_dig(hex[d]) * ((int) pow(16.0, pw));
				pw++;
			}
			d--;
		}
	}
	return (res);
}

void	ft_split_to_cord(t_map *map, int r, int c, char *split)
{
	char	*comma;

	comma = ft_strchr(split, ',');
	map->map[(r) * map->col + (map->col - 1) - c] = ft_atoi(split);
	if (comma)
		map->points[(r) * map->col + (map->col - 1) - c].color
			= ft_hex_to_int(comma + 1);
	else
		map->points[(r) * map->col + (map->col - 1) - c].color = 16777215;
}
