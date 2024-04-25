/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:00:03 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/03/14 16:29:32 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exec_child2(t_data *p, t_parser *node, t_list *aux)
{
	if (p->heredoc_flag)
	{
		if (dup2(p->heredoc_tmp, STDIN_FILENO) == -1)
			return (msg_err("dup infile"));
		close(p->heredoc_tmp);
	}
	else if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			return (msg_err("dup infile"));
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			return (msg_err("dup outfile"));
		close(node->outfile);
	}
	else if (aux->next != NULL)
	{
		if (dup2(p->fd[1], STDOUT_FILENO) == -1)
			return (msg_err("dup pipe out"));
	}
	return (EXIT_SUCCESS);
}

int	exec_child(t_data *p, t_parser *node, t_list *aux, char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (exec_child2(p, node, aux) == EXIT_FAILURE)
		return (g_status = 1, EXIT_FAILURE);
	close(p->fd[1]);
	close(p->fd[0]);
	g_status = execve(node->full_path, node->full_cmd, env);
	exit(EXIT_SUCCESS);
}

void	exec_father(t_data *p, t_list *aux)
{
	if (aux->next && !((t_parser *)aux->next->content)->infile)
		((t_parser *)aux->next->content)->infile = p->fd[0];
	else
		close(p->fd[0]);
	close(p->fd[1]);
	waitpid(p->pid, &p->wait, 0);
}

void	exec_cmd2(t_data *p, char **env, t_parser *node)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (p->heredoc_flag)
		dup2(p->heredoc_tmp, STDIN_FILENO);
	else
		dup2(node->infile, STDIN_FILENO);
	if (node->outfile != STDOUT_FILENO)
		dup2(node->outfile, STDOUT_FILENO);
	if (p->heredoc_flag)
	{
		unlink("here_doc.tmp");
		p->heredoc_flag = 0;
	}
	g_status = execve(node->full_path, node->full_cmd, env);
}
