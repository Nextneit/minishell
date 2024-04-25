/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:38:55 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/03/14 16:30:03 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exec_builtins(t_parser *node, t_data *p)
{
	if (node->full_cmd[0]
		&& ft_strncmp(node->full_cmd[0], "pwd\0", 4) == EXIT_SUCCESS)
		exec_pwd(p);
	if (node->full_cmd[0]
		&& ft_strncmp(node->full_cmd[0], "env\0", 4) == EXIT_SUCCESS)
		exec_env(p);
	if (node->full_cmd[0]
		&& ft_strncmp(node->full_cmd[0], "export\0", 7) == EXIT_SUCCESS)
		exec_export(p, p->lex2, 1);
	if (node->full_cmd[0]
		&& ft_strncmp(node->full_cmd[0], "unset\0", 6) == EXIT_SUCCESS)
		exec_unset(p, p->lex2[1]);
	if (node->full_cmd[0]
		&& ft_strncmp(node->full_cmd[0], "echo\0", 5) == EXIT_SUCCESS)
		flag_echo(p->lex2, 0, p);
	if (node->full_cmd[0]
		&& ft_strncmp(node->full_cmd[0], "cd\0", 3) == EXIT_SUCCESS)
		exec_cd(p, p->lex2, 0);
	if (node->full_cmd[0]
		&& ft_strncmp(node->full_cmd[0], "exit\0", 5) == EXIT_SUCCESS)
	{
		if (final_exit(p, node) == EXIT_FAILURE)
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

static int	exec_cmd(t_data *p, char **env)
{
	t_parser	*node;
	t_list		*aux;

	aux = p->lst_cmd;
	node = ((t_parser *)aux->content);
	if (node->full_path == NULL)
	{
		g_status = 127;
		return (printf("PACOSHELL: %s: command not found\n",
				((t_parser *)p->lst_cmd->content)->full_cmd[0]), 127);
	}
	if (exec_errors(p, node, aux) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	p->pid = fork();
	if (p->pid == -1)
		return (msg_err("fork"), g_status = 1, EXIT_FAILURE);
	if (p->pid == 0)
		exec_cmd2(p, env, node);
	else
		waitpid(p->pid, &p->wait, 0);
	if (check_f_d(node) == 0)
		g_status = 1;
	return (EXIT_SUCCESS);
}

static int	exec_pipe_cmd2(t_data *p, char **env, t_parser *node, t_list *aux)
{
	if (node->full_path == NULL)
		return (printf("PACOSHELL: %s: command not found\n", node->full_cmd[0]),
			g_status = 127, EXIT_FAILURE);
	if (exec_errors(p, node, aux) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pipe(p->fd) == -1)
		msg_err("pipe_cmds");
	p->pid = fork();
	if (p->pid == -1)
	{
		close(p->fd[0]);
		close(p->fd[1]);
		msg_err("fork_cmds");
	}
	if (p->pid == 0)
	{
		if (exec_child(p, node, aux, env) == EXIT_FAILURE)
			return (g_status);
	}
	else
		exec_father(p, aux);
	return (g_status);
}

static int	exec_pipe_cmd(t_data *p, char **env)
{
	t_parser	*node;
	t_list		*aux;

	aux = p->lst_cmd;
	while (aux)
	{
		node = ((t_parser *)aux->content);
		if (exec_pipe_cmd2(p, env, node, aux) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		aux = aux->next;
	}
	return (EXIT_SUCCESS);
}

int	executer(t_data *p, char **env, t_parser *node)
{
	signal(SIGINT, cat_ctrlc);
	signal(SIGQUIT, cat_ctrlbackslash);
	if (node && node->full_cmd && node->full_cmd[0]
		&& check_builtin(p) == EXIT_SUCCESS)
		exec_builtins(((t_parser *)p->lst_cmd->content), p);
	else if (node && node->full_cmd && node->full_cmd[0]
		&& check_builtin(p) == EXIT_FAILURE)
	{
		if (p->pipe_flag)
			exec_pipe_cmd(p, env);
		else if (!p->pipe_flag)
			exec_cmd(p, env);
	}
	else if (node && !node->full_cmd && !node->full_path)
		return (g_status = 0, EXIT_SUCCESS);
	else
	{
		if (node && !node->full_cmd)
		{
			printf("PACOSHELL: %s: command not found\n", node->full_cmd[0]);
			return (g_status = 127, EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
