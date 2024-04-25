/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:19:31 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/14 16:30:39 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_unset_continue(t_env *del)
{
	free(del->name);
	if (del->content != NULL)
		free(del->content);
	free(del);
	del = NULL;
}

void	exec_unset(t_data *p, char *name)
{
	t_env	*del;
	t_env	*prev;

	if (!name)
		return ;
	p->aux = p->l_env;
	prev = NULL;
	while (p->aux != NULL)
	{
		if (!ft_strncmp(p->aux->name, name, ft_strlen(name)))
		{
			del = p->aux;
			if (prev)
				prev->next_env = p->aux->next_env;
			else
				p->l_env = p->aux->next_env;
			exec_unset_continue(del);
			g_status = 0;
			return ;
		}
		prev = p->aux;
		p->aux = p->aux->next_env;
	}
	check_path(p);
	g_status = 1;
}

void	exec_pwd(t_data *p)
{
	char	dir[500];

	p->act_dir = getcwd(dir, 500);
	if (p->act_dir == NULL)
		return ;
	ft_printf("%s\n", p->act_dir);
	g_status = 0;
}

void	exec_cd(t_data *p, char **s, int flag)
{
	char	dir[500];

	if (ft_strncmp(s[0], "cd\0", 3) == EXIT_SUCCESS && s[1] == NULL)
		change_cd(p);
	else if (!ft_strncmp(s[0], "cd\0", 3) && s[1])
	{
		getcwd(dir, 500);
		flag = chdir(s[1]);
		if (flag == 0)
		{
			change_oldpwd2(p, dir);
			change_pwd(p);
		}
		else if (flag == -1)
		{
			p->tmp = ft_strjoin("bash: cd: ", s[1]);
			if (!p->tmp)
				return ;
			p->cd_error = ft_strjoin(p->tmp, ": No such file or directory");
			if (!p->cd_error)
				return ;
			ft_putendl_fd(p->cd_error, 2);
			free_cd_error(p);
		}
	}
}

int	final_exit(t_data *p, t_parser *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (node->full_cmd[i] != NULL)
		i++;
	if (i > 2)
		return (printf("exit\nPACOSHELL: exit: too many arguments\n"),
			EXIT_FAILURE);
	if (i >= 2)
	{
		while (node->full_cmd[1][j] != '\0')
		{
			if (ft_isdigit(node->full_cmd[1][j]) == 0)
			{
				printf("exit\nPACOSHELL: exit: %s: numeric argument required\n",
					node->full_cmd[1]);
				break ;
			}
			j++;
		}
	}
	free_path(p);
	exit(g_status);
}
