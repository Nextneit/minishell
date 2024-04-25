/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:04:22 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/06 11:59:49 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	x;

	x = 0;
	if (ft_strlen(s1) < 1 || ft_strlen(s2) < 1)
		return (EXIT_FAILURE);
	if (n == 0)
		return (0);
	while (((s1[x] != '\0') || (s2[x] != '\0')) && x < n)
	{
		if ((size_t)s1[x] > (size_t)s2[x])
			return (1);
		if ((size_t)s1[x] < (size_t)s2[x])
			return (-1);
		x++;
	}
	return (0);
}
