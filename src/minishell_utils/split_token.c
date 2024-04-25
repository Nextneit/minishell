/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:01:04 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/14 16:26:08 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	word_len(char *s, t_data *p)
{
	size_t	len;
	int		fq_simple;
	int		fq_double;

	len = 0;
	fq_simple = 0;
	fq_double = 0;
	p->l = -1;
	while (s[++p->l] != '\0')
	{
		if (s[p->l] == '\'' && !fq_double)
			fq_simple = !fq_simple;
		if (s[p->l] == '\"' && !fq_simple)
			fq_double = !fq_double;
		if ((s[p->l] == '|' || s[p->l] == '>' || s[p->l] == '<')
			&& (!fq_double && !fq_simple))
			return (len + 1);
		else
			len++;
		if ((s[p->l + 1] == '|' || s[p->l + 1] == '>' || s[p->l + 1] == '<')
			&& (!fq_double && !fq_simple))
			return (len);
	}
	return (len);
}

static void	count_words2(char **s, int *fq_simple, int *fq_double, t_data *p)
{
	if (s[p->i][p->j] == '\'' && !*fq_double)
	{
		if (*fq_simple)
		{
			p->count++;
			p->wc = 0;
		}
		*fq_simple = !*fq_simple;
	}
	if (s[p->i][p->j] == '\"' && !*fq_simple)
	{
		if (*fq_double)
		{
			p->count++;
			p->wc = 0;
		}
		*fq_double = !*fq_double;
	}
	if (s[p->i][p->j] != '\'' && s[p->i][p->j] != '\"' && s[p->i][p->j] != '|'
		&& s[p->i][p->j] != '>' && s[p->i][p->j] != '<' && p->wc && !*fq_double
		&& !*fq_simple)
	{
		p->count++;
		p->wc = !p->wc;
	}
}

static int	count_words(char **s, t_data *p)
{
	int		fq_simple;
	int		fq_double;

	fq_simple = 0;
	fq_double = 0;
	p->i = 0;
	p->count = 0;
	while (s[p->i] != NULL)
	{
		p->j = 0;
		p->wc = 1;
		while (s[p->i][p->j] != '\0')
		{
			count_words2(s, &fq_simple, &fq_double, p);
			if ((s[p->i][p->j] == '<' || s[p->i][p->j] == '|'
				|| s[p->i][p->j] == '>') && !fq_simple && !fq_double)
			{
				p->count++;
				p->wc = 1;
			}
			p->j++;
		}
		p->i++;
	}
	return (p->count);
}

char	**split_pipe(char **s, t_data *p, int i, int j)
{
	char	**str;

	p->n_split = 0;
	str = malloc((count_words(s, p) + 1) * sizeof(char **));
	if (!str)
		return (NULL);
	while (s[++i] != NULL)
	{
		j = 0;
		while (s[i][j] != '\0')
		{
			if (s[i][j] == '\0')
				break ;
			p->wordle = word_len(s[i] + j, p);
			str[p->n_split] = ft_substr(s[i], j, p->wordle);
			if (!str[p->n_split])
				return (free_mini_split(str, p->n_split), NULL);
			j += p->wordle;
			p->n_split++;
		}
	}
	if (s[0] && s[0][0] == '\0')
		str[p->n_split] = ft_strdup("");
	str[p->n_split] = NULL;
	return (str);
}
