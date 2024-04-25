/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:01:33 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/03/14 16:25:06 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_struct2(t_data *p)
{
	p->c = 0;
	p->i = 0;
	p->j = 0;
	p->l = 0;
	p->count = 0;
	p->double_flag = 0;
	p->heredoc_flag = 0;
	p->n_split = 0;
	p->path_flag = 1;
	p->pid = 0;
	p->pipe_flag = 0;
	p->simple_flag = 0;
	p->total_expr = 0;
	p->wait = 0;
	p->wc = 1;
	p->wordle = 0;
	p->dup_stdin = dup(STDIN_FILENO);
	p->dup_stdout = dup(STDOUT_FILENO);
}

void	init_struct(t_data *p)
{
	p->act_dir = NULL;
	p->aux = NULL;
	p->cd_error = NULL;
	p->eof = NULL;
	p->heredoc_line = NULL;
	p->l_env = NULL;
	p->lex = NULL;
	p->lex2 = NULL;
	p->line = NULL;
	p->path = NULL;
	p->shell = NULL;
	p->tmp = NULL;
	init_struct2(p);
}
