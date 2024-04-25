/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:11:23 by etornay-          #+#    #+#             */
/*   Updated: 2023/05/09 14:48:16 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*p;
	unsigned char	x;

	p = s + ft_strlen(s) - 1;
	x = (unsigned char)c;
	if (!s)
		return (0);
	if (x == '\0')
		return ((char *)(p + 1));
	while (p >= s)
	{
		if (*p == x)
		{
			return ((char *)p);
		}
		p--;
	}
	return (0);
}
