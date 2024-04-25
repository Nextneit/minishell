/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:28:00 by etornay-          #+#    #+#             */
/*   Updated: 2023/05/09 13:58:58 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	x;

	if (!dest && !src)
		return (0);
	x = 0;
	if ((size_t)dest - (size_t)src < n)
	{
		x = n - 1;
		while (x > 0)
		{
			((char *)dest)[x] = ((const char *)src)[x];
			x--;
		}
		((char *)dest)[x] = ((const char *)src)[x];
	}
	else
	{
		while (x < n)
		{
			((char *)dest)[x] = ((const char *)src)[x];
			x++;
		}
	}
	return (dest);
}
