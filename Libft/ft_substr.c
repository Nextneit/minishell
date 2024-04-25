/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:53:28 by etornay-          #+#    #+#             */
/*   Updated: 2023/05/09 13:58:58 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	x;
	size_t	y;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len >= ft_strlen(s))
		len = (ft_strlen(s) - start);
	str = malloc((len + 1) * (sizeof(char)));
	if (!s || !str)
		return (0);
	x = start;
	y = 0;
	while ((x < ft_strlen(s)) && (y < len))
	{
		str[y++] = s[x++];
	}
	str[y] = '\0';
	return (str);
}

/* int main (int argc, char **argv)
{
	char s[5];
	int start;
	int len;

	len = 4;
	start = 1;
	s = ("hola\0");
	ft_substr(s, start, len);
}
 */