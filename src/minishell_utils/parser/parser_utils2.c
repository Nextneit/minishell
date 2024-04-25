/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:04:59 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/14 16:28:22 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	flag_pipe(t_data *p, int *i)
{
	if (p->lex2[0][0] == '|' && p->lex2[*i + 1] && p->lex2[*i + 1][0] == '|')
	{
		printf("PACOSHELL: syntax error near unexpected token `||'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i] && p->lex2[*i][0] == '|' && p->lex2[*i + 1] == NULL)
	{
		printf("PACOSHELL: syntax error near unexpected token `|'\n");
		return (EXIT_FAILURE);
	}
	else if (p->lex2[*i] == NULL && p->lex2[*i - 1][0] == '|')
	{
		printf("PACOSHELL: syntax error near unexpected token `|'\n");
		return (EXIT_FAILURE);
	}
	if (p->lex2[*i] && p->lex2[*i][0] == '|')
	{
		p->pipe_flag = 1;
		(*i)++;
	}
	return (EXIT_SUCCESS);
}

void	read_only(t_data *p, t_parser *node, int *i)
{
	node->infile = open(p->lex2[*i + 1], O_RDONLY);
	if (node->infile < 0)
		return ;
}

void	exec_trunc(t_data *p, t_parser *node, int *i)
{
	node->outfile = open(p->lex2[*i + 1], O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	if (node->outfile < 0)
		return ;
}

void	exec_append(t_data *p, t_parser *node, int *i)
{
	if (p->lex2[*i + 2])
	{
		node->outfile = open(p->lex2[*i + 2], O_WRONLY | O_CREAT
				| O_APPEND, 0644);
		if (node->outfile > 0)
			return ;
	}
	else
	{
		p->clean = ft_lstnew(node);
		free_cmd_list(&p->clean);
		printf("PACOSHELL: syntax error near unexpected token `newline'\n");
		return ;
	}
}

int	check_builtin(t_data *p)
{
	if (ft_strncmp(p->lex2[0], "pwd\0", 4) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (ft_strncmp(p->lex2[0], "env\0", 4) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (ft_strncmp(p->lex2[0], "export\0", 7) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (ft_strncmp(p->lex2[0], "unset\0", 6) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (ft_strncmp(p->lex2[0], "echo\0", 5) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (ft_strncmp(p->lex2[0], "cd\0", 3) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (ft_strncmp(p->lex2[0], "exit\0", 5) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
