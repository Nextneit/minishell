/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:27:59 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/03/14 16:24:57 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_env_content(t_data *p, char *s)
{
	char	*status;

	p->aux = p->l_env;
	if (ft_strncmp(s, "?", 1) == EXIT_SUCCESS)
	{
		status = ft_itoa(g_status);
		return (status);
	}
	while (p->aux)
	{
		if (ft_strncmp(p->aux->name, s, ft_strlen(s)) == EXIT_SUCCESS)
			return (ft_strdup(p->aux->content));
		p->aux = p->aux->next_env;
	}
	return (ft_strdup(""));
}

static void	expand_1(t_data *p, int	*i, int *flag, char **expand)
{
	char	*tmp;

	if (p->lex[p->i][p->k] == '$' && !*flag)
	{
		if (p->lex[p->i][p->k + 1] == '\0' || p->lex[p->i][p->k + 1] == ' ')
		{
			*expand = ft_strjoin_gnl2(*expand, ft_strdup("$"));
			p->k++;
		}
		else
		{
			p->k++;
			*i = p->k;
			while ((p->lex[p->i][p->k] != ' ' && p->lex[p->i][p->k] != '$'
				&& p->lex[p->i][p->k] != '\0') && p->lex[p->i][p->k] != '\''
				&& p->lex[p->i][p->k] != '\"')
				p->k++;
			tmp = ft_substr(p->lex[p->i], *i, p->k - *i);
			*expand = ft_strjoin_gnl2(*expand, get_env_content(p, tmp));
			free(tmp);
			tmp = NULL;
		}
	}
}

static void	expand_2(t_data *p, int *i, int *flag, char **exp)
{
	if ((!*flag && p->lex[p->i][p->k] == '~')
		&& ((p->lex[p->i][p->k - 1] == ' ' && p->lex[p->i][p->k + 1] == ' ')
		|| (p->lex[p->i][p->k + 1] == '\0')
		|| (p->lex[p->i][p->k + 1] == '/')))
	{
		if (p->lex[p->i][p->j] == '\'')
			*flag = !*flag;
		*exp = ft_strjoin_gnl2(*exp, get_env_content(p, "HOME"));
		p->k++;
	}
	else
	{
		*i = p->k;
		while ((p->lex[p->i][p->k] != '$' || *flag)
			&& p->lex[p->i][p->k] != '\0')
		{
			if (p->lex[p->i][p->k] == '\'')
				*flag = !*flag;
			p->k++;
		}
		*exp = ft_strjoin_gnl2(*exp, ft_substr(p->lex[p->i], *i, p->k - *i));
	}
}

void	expand(t_data *p)
{
	int		i;
	int		flag;
	char	*expand;

	expand = NULL;
	flag = 0;
	p->i = -1;
	while (p->lex[++p->i])
	{
		p->k = 0;
		i = 0;
		while (p->lex[p->i][p->k])
		{
			expand_1(p, &i, &flag, &expand);
			expand_2(p, &i, &flag, &expand);
		}
		free(p->lex[p->i]);
		p->lex[p->i] = NULL;
		p->lex[p->i] = ft_strdup(expand);
		free(expand);
		expand = NULL;
	}
	p->i = 0;
}
