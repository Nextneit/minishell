/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:19:52 by etornay-          #+#    #+#             */
/*   Updated: 2023/05/05 17:15:26 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != '\0')
			count++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (count);
}

static void	ft_free_split(char **arr, size_t index)
{
	size_t	i;

	if (arr != NULL)
	{
		i = 0;
		while (i < index)
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
		free(arr);
	}
}

static size_t	word_length(const char *s, char delimiter)
{
	size_t	len;

	len = 0;
	while (s[len] != delimiter && s[len] != '\0')
		len++;
	return (len);
}

static char	**split_loop(const char *s, char delimiter, char **new_str)
{
	size_t	i;
	size_t	word_len;

	i = 0;
	while (*s != '\0')
	{
		while (*s == delimiter && *s != '\0')
			s++;
		if (*s == '\0')
			break ;
		word_len = word_length(s, delimiter);
		new_str[i] = (char *)malloc((word_len + 1) * sizeof(char));
		if (!new_str[i])
		{
			ft_free_split(new_str, i);
			return (NULL);
		}
		ft_strlcpy(new_str[i], (char *)s, word_len + 1);
		s += word_len;
		i++;
	}
	new_str[i] = NULL;
	return (new_str);
}

char	**ft_split(const char *s, char delimiter)
{
	char	**new_str;

	new_str = (char **)malloc((count_words(s, delimiter) + 1) * sizeof(char *));
	if (!new_str || !s)
		return (NULL);
	new_str = split_loop(s, delimiter, new_str);
	if (!new_str)
	{
		ft_free_split(new_str, count_words(s, delimiter));
		return (NULL);
	}
	return (new_str);
}
