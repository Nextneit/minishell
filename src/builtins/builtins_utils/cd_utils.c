/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:50:53 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/03/14 16:31:28 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_cd_path(t_data *p, char *s)
{
	p->aux = p->l_env;
	while (p->aux)
	{
		if (ft_strncmp(p->aux->name, s, ft_strlen(s)) == EXIT_SUCCESS)
		{
			p->tmp = p->aux->content;
			break ;
		}
		p->aux = p->aux->next_env;
	}
}

void	change_pwd(t_data *p)
{
	char	dir[500];

	p->aux = p->l_env;
	while (p->aux)
	{
		if (ft_strncmp(p->aux->name, "PWD", 3) == EXIT_SUCCESS)
		{
			free(p->aux->content);
			p->aux->content = ft_strdup(getcwd(dir, 500));
			if (!p->aux->content)
				return ;
			break ;
		}
		p->aux = p->aux->next_env;
	}
	g_status = 0;
}

void	change_oldpwd(t_data *p)
{
	char	dir[500];

	p->aux = p->l_env;
	while (p->aux)
	{
		if (ft_strncmp(p->aux->name, "OLDPWD", 6) == EXIT_SUCCESS)
		{
			free(p->aux->content);
			p->aux->content = ft_strdup(getcwd(dir, 500));
			if (!p->aux->content)
				return ;
			break ;
		}
		p->aux = p->aux->next_env;
	}
}

void	change_oldpwd2(t_data *p, char *dir)
{
	p->aux = p->l_env;
	while (p->aux)
	{
		if (ft_strncmp(p->aux->name, "OLDPWD", 6) == 0)
		{
			free(p->aux->content);
			p->aux->content = ft_strdup(dir);
			if (!p->aux->content)
				return ;
			break ;
		}
		p->aux = p->aux->next_env;
	}
}

void	change_cd(t_data *p)
{
	change_oldpwd(p);
	get_cd_path(p, "HOME\0");
	chdir(p->tmp);
	change_pwd(p);
	g_status = 0;
}
