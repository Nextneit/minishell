/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:03:57 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/14 16:30:54 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	re_path(t_data *p)
{
	t_env	*aux;

	aux = p->l_env;
	if (p->path != NULL)
		free_path(p);
	while (aux)
	{
		if (!ft_strncmp("PATH", aux->name, 4))
			break ;
		aux = aux->next_env;
	}
	p->path = ft_split(aux->content, ':');
	if (!p->path)
		return ;
}

void	check_path(t_data *p)
{
	t_env	*aux;

	aux = p->l_env;
	while (aux)
	{
		if (!ft_strncmp(aux->name, "PATH", 4))
		{
			p->path_flag = 1;
			return ;
		}
		else
			p->path_flag = 0;
		aux = aux->next_env;
	}
}
