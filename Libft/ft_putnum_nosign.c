/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum_nosign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:33:59 by etornay-          #+#    #+#             */
/*   Updated: 2023/11/07 16:11:02 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnum_nosign(unsigned int number)
{
	int	x;

	x = 0;
	if (number > 9)
	{
		x = ft_putnum_nosign(number / 10);
		if (x == -1)
			return (-1);
		number = number % 10;
	}
	if (number <= 9)
	{
		if (ft_putchar('0' + number) == -1)
			return (-1);
		x++;
	}
	return (x);
}
