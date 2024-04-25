/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:20:24 by etornay-          #+#    #+#             */
/*   Updated: 2023/05/05 13:24:44 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wwe(long int w)
{
	int	z;

	z = 0;
	while (w >= 10)
	{
		w /= 10;
		z++;
	}
	return (z);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	w;
	int			x;

	w = n;
	x = 0;
	if (n < 0)
	{
		w *= -1;
		x = 1;
	}
	x = ft_wwe(w) + x + 1;
	str = (char *)malloc((x + 1) * (sizeof(char)));
	if (!str)
		return (0);
	str[x--] = '\0';
	while (x >= 0)
	{
		str[x] = w % 10 + '0';
		w /= 10;
		x--;
		if (n < 0)
			str[0] = '-';
	}
	return (str);
}
