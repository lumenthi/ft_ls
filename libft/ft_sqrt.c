/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:51:11 by lumenthi          #+#    #+#             */
/*   Updated: 2017/11/23 16:52:13 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(int nb)
{
	int i;
	int r;

	i = 1;
	while (i <= (nb / 2))
	{
		r = i * i;
		if (r == nb)
			return (i);
		i++;
	}
	return (0);
}