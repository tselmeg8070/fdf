/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:36:58 by tadiyamu          #+#    #+#             */
/*   Updated: 2022/12/29 16:15:17 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *dist, size_t n)
{
	unsigned char	*cpy;

	cpy = (unsigned char *) dist;
	while (0 < n)
	{
		*cpy = 0;
		cpy++;
		n--;
	}
}
