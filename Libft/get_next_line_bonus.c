/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:57:40 by etornay-          #+#    #+#             */
/*   Updated: 2023/09/26 12:31:48 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*clean(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (str = NULL, NULL);
	}
	result = ft_calloc_gnl((ft_strlen_gnl(str) - i + 1), sizeof(char));
	if (result == NULL)
		return (free(str), str = NULL, NULL);
	i++;
	j = 0;
	while (str[i] != '\0')
		result[j++] = str[i++];
	result[j] = '\0';
	return (free(str), str = NULL, result);
}

static char	*get_line(char *str)
{
	char	*act;
	int		i;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	act = ft_calloc_gnl(i + 1 + (str[i] == '\n'), sizeof(char));
	if (act == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		act[i] = str[i];
		i++;
	}
	if (str[i] != '\0' && str[i] == '\n')
		act[i++] = '\n';
	act[i] = '\0';
	return (act);
}

static char	*read_fd(int fd, char *str)
{
	char	*save;
	int		count;

	count = 1;
	save = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (save == NULL)
		return (free(save), free(str), str = NULL, NULL);
	while (!ft_strchr_gnl(save, '\n') && count != 0)
	{
		count = read(fd, save, BUFFER_SIZE);
		if (count < 0)
			return (free(save), NULL);
		save[count] = '\0';
		str = ft_strjoin_gnl(str, save);
		if (str == NULL)
			return (free(save), free(str), str = NULL, NULL);
	}
	return (free(save), str);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (str[fd] != NULL)
		{
			free(str[fd]);
			str[fd] = NULL;
		}
		return (NULL);
	}
	str[fd] = read_fd(fd, str[fd]);
	if (str[fd] == NULL)
		return (free(str[fd]), str[fd] = NULL, NULL);
	line = get_line(str[fd]);
	if (line == NULL)
		return (free(str[fd]), str[fd] = NULL, NULL);
	str[fd] = clean(str[fd]);
	if (str[fd] == NULL)
		return (free(str[fd]), str[fd] = NULL, line);
	return (line);
}
/* #include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fichero1;
	int		fichero2;
	int		fichero3;
	char	*line;

	fichero1 = open("text.txt", 0);
	fichero2 = open("text2.txt", O_RDONLY);
	fichero3 = open("text3.txt", O_RDONLY);
	line = get_next_line(fichero1);
	while (line != NULL)
	{
		printf("%s", line);
		line = get_next_line(fichero1);
	}
	printf("\n\n");
	line = get_next_line(fichero2);
	while (line != NULL)
	{
		printf("%s", line);
		line = get_next_line(fichero2);
	}
	printf("\n\n");
	line = get_next_line(fichero3);
	while (line != NULL)
	{
		printf("%s", line);
		line = get_next_line(fichero3);
	}
	printf("\n\n");
	close(fichero1);
	close(fichero2);
	close(fichero3);
	free(line);
} */