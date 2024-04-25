/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ga <ncruz-ga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:10:25 by etornay-          #+#    #+#             */
/*   Updated: 2024/04/22 17:22:13 by ncruz-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	ft_leaks()
{
	system("leaks -q minishell");
}*/

void	path(t_data *p)
{
	check_path(p);
	if (p->path_flag == 0)
		free_path(p);
	if (p->path_flag)
		re_path(p);
}

int	input(char *input, t_data *p, char **env)
{
	t_parser	*node;

	path(p);
	p->lex = split_line(input, ' ', p);
	if (p->lex == NULL)
		return (printf("Unclosed quotes\n"), EXIT_SUCCESS);
	expand(p);
	if (p->lex != NULL)
	{
		p->lex2 = split_pipe(p->lex, p, -1, 0);
		free_lex(p);
	}
	if (p->lex2[0] == NULL)
		return (EXIT_SUCCESS);
	if (parser_cmd(p, 0) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	node = ((t_parser *)p->lst_cmd->content);
	if (executer(p, env, node) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	if (p->heredoc_flag == 1)
	{
		unlink("here_doc.tmp");
		p->heredoc_flag = 0;
	}
	return (EXIT_SUCCESS);
}

static int	minishell_exit(t_data *p)
{
	signal(SIGINT, signals);
	signal(SIGQUIT, SIG_IGN);
	if (prompt(p) == EXIT_FAILURE)
	{
		printf("exit\n");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	minishell(t_data *p, char **env)
{
	ft_paco_sanz();
	if (get_path(p, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_env(p, env, 0);
	while (33)
	{
		minishell_exit(p);
		if (ft_strncmp(p->line, "\0", 1) == EXIT_FAILURE)
			add_history(p->line);
		if (input(p->line, p, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (p->line != NULL)
		{
			free(p->line);
			p->line = NULL;
		}
		if (p->lex2 != NULL)
			free_lex2(p);
		free_cmd_list(&p->lst_cmd);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*p;

	(void)argc;
	(void)argv;
	p = ft_calloc(1, sizeof(t_data));
	if (p == NULL)
		exit (EXIT_FAILURE);
	init_struct(p);
	if (minishell(p, env) == EXIT_FAILURE)
	{
		free_all(p);
		exit(EXIT_FAILURE);
	}
	free_all(p);
	return (EXIT_SUCCESS);
}
