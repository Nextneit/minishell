/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:10:25 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/14 16:27:42 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	msg_error(char *str)
{
	perror(str);
	unlink("here_doc.tmp");
	return (EXIT_FAILURE);
}

void	ft_heredoc(t_data *p, char *limit)
{
	p->eof = ft_strjoin(limit, "\n");
	p->heredoc_tmp = open("here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (43)
	{
		write(1, "> ", 2);
		p->heredoc_line = get_next_line(p->dup_stdin);
		if (!p->heredoc_line)
			msg_error("Line");
		if (!ft_strncmp(p->eof, p->heredoc_line, ft_strlen(p->heredoc_line)))
		{
			free(p->eof);
			free(p->heredoc_line);
			p->heredoc_line = NULL;
			close(p->dup_stdin);
			get_next_line(p->dup_stdin);
			break ;
		}
		write(p->heredoc_tmp, p->heredoc_line, ft_strlen(p->heredoc_line));
		free(p->heredoc_line);
	}
	close(p->heredoc_tmp);
	p->heredoc_tmp = open("here_doc.tmp", O_RDONLY);
	p->dup_stdin = dup(STDIN_FILENO);
}

void	exec_heredoc(t_data *p, t_parser *node, int *i)
{
	if (p->lex2[*i + 2] && p->lex2[*i + 2][0] == '<')
		return ;
	if (p->lex2[*i + 2])
	{
		p->heredoc_flag = 1;
		ft_heredoc(p, p->lex2[*i + 2]);
		node->infile = p->heredoc_tmp;
	}
	else
	{
		p->clean = ft_lstnew(node);
		free_cmd_list(&p->clean);
		return ;
	}
}
