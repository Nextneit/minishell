/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:47:07 by etornay-          #+#    #+#             */
/*   Updated: 2023/05/09 13:58:58 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*total;
	size_t	x;
	size_t	y;

	x = ft_strlen(s1);
	y = ft_strlen(s2);
	if (!s1 || !s2)
		return (0);
	total = (char *)malloc((x + y + 1) * (sizeof(char)));
	if (!total)
		return (0);
	ft_memcpy(total, s1, x);
	ft_memcpy(total + x, s2, y);
	total[x + y] = '\0';
	return (total);
}
