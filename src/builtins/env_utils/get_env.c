/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:11:15 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/03/14 16:31:09 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_path(t_data *p, char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	p->path = ft_split(env[i] + 5, ':');
	if (!p->path)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	lst_addenv_back(t_env **lst, t_env *new, char **tmp)
{
	t_env	*first;

	if (new == NULL)
		return ;
	if (tmp != NULL)
	{
		new->name = ft_strdup(tmp[0]);
		if (tmp[1] == NULL)
			new->content = ft_strdup("=");
		else
			new->content = ft_strdup(tmp[1]);
		new->index = 0;
		new->next_env = NULL;
	}
	first = *lst;
	if (first == NULL)
	{
		first = new;
		return ;
	}
	while (first->next_env != NULL)
		first = first->next_env;
	first->next_env = new;
	return ;
}

void	init_env(t_data *p, char **env, int i)
{
	char	**tmp;

	p->l_env = calloc(1, sizeof(t_env));
	if (!p->l_env)
		return ;
	tmp = ft_split(env[i], '=');
	if (!tmp)
		return ;
	p->l_env->name = ft_strdup(tmp[0]);
	p->l_env->content = ft_strdup(tmp[1]);
	p->l_env->next_env = NULL;
	p->l_env->index = 0;
	while (env[++i] != NULL)
	{
		free_split(tmp);
		p->aux = ft_calloc(1, sizeof(t_env));
		if (!p->aux)
			return ;
		tmp = ft_split(env[i], '=');
		if (!tmp)
			return ;
		lst_addenv_back(&p->l_env, p->aux, tmp);
	}
	free_split(tmp);
	set_env_index(p);
}

void	exec_env(t_data *p)
{
	p->aux = p->l_env;
	while (p->aux != NULL)
	{
		if (ft_strncmp(p->aux->content, "\"\"\0", 3) == EXIT_SUCCESS)
			p->aux = p->aux->next_env;
		else
		{
			printf ("%s=%s\n", p->aux->name, p->aux->content);
			p->aux = p->aux->next_env;
		}
	}
	g_status = 0;
}
