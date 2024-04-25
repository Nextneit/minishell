/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:42:29 by etornay-          #+#    #+#             */
/*   Updated: 2023/09/26 12:33:57 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_auxpointer(char *base, unsigned long long n, int z)
{
	if (n >= 16)
	{
		z += ft_auxpointer(base, n / 16, z);
		if (z == -1)
			return (-1);
	}
	if (write (1, &base[n % 16], 1) == -1)
		return (-1);
	z++;
	return (z);
}

int	ft_putpointer(unsigned long long pointer)
{
	unsigned long long	p;
	int					x;

	x = 0;
	p = (unsigned long long)pointer;
	if (write(1, "0x", 2) != 2)
		return (-1);
	x = ft_auxpointer("0123456789abcdef", p, x);
	if (x == -1)
		return (-1);
	x += 2;
	return (x);
}
