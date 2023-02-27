/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 21:28:02 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/02/25 21:28:05 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_input(int keysym, t_vars *vars)
{
	if (keysym == 65307 && vars->win != 0)
	{
		mlx_loop_end(vars->mlx);
	}
	return (0);
}

int	handle_cross(t_vars *vars)
{
	if (vars->win != 0)
		return (handle_input(65307, vars));
	return (0);
}

/* This function needs to exist, but it is useless for the moment */
int	handle_no_event(void)
{
	return (0);
}
