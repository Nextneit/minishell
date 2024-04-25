/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum_dec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:39:26 by etornay-          #+#    #+#             */
/*   Updated: 2023/09/26 12:34:04 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		n = 147483648;
	}
	else if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n >= 0 && n <= 9)
	{
		ft_putchar(n + '0');
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

static int	ft_digitcount(int nb)
{
	int	i;

	i = 0;
	while (nb >= 10)
	{
		i++;
		nb /= 10;
	}
	return (i + 1);
}

int	ft_putnum_dec(int x)
{
	long int	nb;

	nb = 0;
	if (x == -2147483648)
	{
		ft_putnbr(x);
		return (11);
	}
	ft_putnbr(x);
	if (x >= 0)
		return (ft_digitcount(x));
	nb = (long int)x * (-1);
	return (ft_digitcount(nb) + 1);
}
