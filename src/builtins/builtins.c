/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 08:51:03 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/03/14 16:30:19 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_export2(t_data *p, char *s, char **tmp)
{
	t_env	*new;

	tmp = split_line(s, '=', p);
	if (!tmp)
		return ;
	if (check_node(p, tmp) == EXIT_SUCCESS)
	{
		free_split(tmp);
		return ;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = ft_strdup(tmp[0]);
	if (tmp[1] == NULL)
		new->content = ft_strdup("\"\"");
	else if (tmp[1] != NULL)
		new->content = ft_strdup(tmp[1]);
	new->index = 0;
	p->aux = p->l_env;
	while (p->aux->next_env != NULL)
		p->aux = p->aux->next_env;
	p->aux->next_env = new;
	new->next_env = NULL;
	free_split(tmp);
}

void	exec_export(t_data *p, char **s, int index)
{
	restart_index(p);
	set_env_index(p);
	p->aux = p->l_env;
	if (s[1] != NULL)
		exec_export2(p, s[1], NULL);
	else if (s[1] == NULL)
	{
		while (p->aux != NULL)
		{
			if (p->aux->index == index)
			{
				if (ft_strncmp(p->aux->content, "\"\"\0", 3) == EXIT_SUCCESS)
					ft_printf("declare -x %s=%s\n",
						p->aux->name, p->aux->content);
				else
					ft_printf("declare -x %s=\"%s\"\n",
						p->aux->name, p->aux->content);
				p->aux = p->l_env;
				index++;
			}
			else if (p->aux->index != index)
				p->aux = p->aux->next_env;
		}
	}
	g_status = 0;
}

static void	exec_echo2(char **s, int size, t_data *p, int *j)
{
	while (s[size][*j])
	{
		if (s[size][*j] == '\"' && !p->simple_flag)
			p->double_flag = !p->double_flag;
		else if (s[size][*j] == '\'' && !p->double_flag)
			p->simple_flag = !p->simple_flag;
		else if (s[size][*j] == '\"' && p->simple_flag)
			ft_printf("%c", s[size][*j]);
		else if (s[size][*j] == '\'' && p->double_flag)
			ft_printf("%c", s[size][*j]);
		else
			ft_printf("%c", s[size][*j]);
		(*j)++;
	}
	g_status = 0;
}

static void	exec_echo(char **s, int size, t_data *p)
{
	int	j;

	j = 0;
	if (s[size][j] == '\0')
		ft_printf("%c", s[size][j]);
	else if (s[size][j] == '\"' && !p->simple_flag)
	{
		j++;
		p->double_flag = !p->double_flag;
	}
	else if (s[size][j] == '\'' && !p->double_flag)
	{
		j++;
		p->simple_flag = !p->simple_flag;
	}
	exec_echo2(s, size, p, &j);
}

void	flag_echo(char **s, int flag, t_data *p)
{
	while (s[p->j])
		p->j++;
	if (p->j > 1 && s[1] != NULL)
	{
		if (ft_strncmp (s[1], "-n\0", 3) == EXIT_SUCCESS)
		{
			flag = 1;
			p->j = 2;
		}
		else
			p->j = 1;
		while (s[p->j] != NULL)
		{
			exec_echo(s, p->j, p);
			if (s[p->j + 1])
				ft_printf(" ");
			p->j++;
			if (p->double_flag == 1)
				p->double_flag = 0;
			if (p->simple_flag == 1)
				p->simple_flag = 0;
		}
	}
	if (flag == 0)
		ft_printf("\n");
}
