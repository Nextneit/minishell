/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:40:49 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/03/14 16:31:38 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	restart_index(t_data *p)
{
	p->aux = p->l_env;
	while (p->aux)
	{
		p->aux->index = 0;
		p->aux = p->aux->next_env;
	}
}

static t_env	*get_first(t_data *p)
{
	t_env	*first;
	int		i;

	i = 1;
	p->aux = p->l_env;
	first = p->l_env;
	while (p->aux != NULL)
	{
		if (ft_exp_cmp(first->name, p->aux->name) < 0
			&& p->aux->index == 0)
			first = p->aux;
		p->aux = p->aux->next_env;
	}
	return (first);
}

void	set_env_index(t_data *p)
{
	int		index;

	index = 1;
	p->first = p->l_env;
	while (index <= ft_env_size(p->l_env))
	{
		p->aux = p->l_env;
		while (p->aux != NULL)
		{
			if (ft_exp_cmp(p->first->name, p->aux->name) > 0
				&& p->aux->index == 0)
				p->first = p->aux;
			p->aux = p->aux->next_env;
		}
		p->first->index = index;
		p->first = get_first(p);
		index++;
	}
}

static void	change_content(t_env *node, char *s)
{
	if (node->content != NULL)
	{
		free(node->content);
		node->content = ft_strdup(s);
	}
	else
		node->content = ft_strdup(s);
}

int	check_node(t_data *p, char **s)
{
	p->aux = p->l_env;
	while (p->aux)
	{
		if (ft_strncmp(p->aux->name, s[0], ft_strlen(s[0])) == EXIT_SUCCESS)
		{
			change_content(p->aux, s[1]);
			return (EXIT_SUCCESS);
		}
		else
			p->aux = p->aux->next_env;
	}
	return (EXIT_FAILURE);
}
