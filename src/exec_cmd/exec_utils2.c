/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:07:02 by etornay-          #+#    #+#             */
/*   Updated: 2024/03/14 16:29:38 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_errors(t_data *p, t_parser *node, t_list *aux)
{
	int	i;

	i = 0;
	if (node->infile == -1 || node->outfile == -1)
	{
		while (p->lex2[i][0] != '<' && p->lex2[i][0] != '>')
			i++;
		if ((p->lex2[i][0] == '<' && p->lex2[i + 1] && p->lex2[i + 1][0] != '<')
			|| (p->lex2[i][0] == '>' && p->lex2[i + 1]
			&& p->lex2[i + 1][0] != '>'))
			printf("PACOSHELL: %s: No such file or directory\n",
				p->lex2[i + 1]);
		else
			printf("PACOSHELL: %s: No such file or directory\n",
				p->lex2[i + 2]);
		aux = aux->next;
		return (g_status = 1, EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	msg_err(char *str)
{
	perror(str);
	unlink("here_doc.tmp");
	return (EXIT_FAILURE);
}

int	check_f_d(t_parser *node)
{
	struct stat	file_info;
	int			i;
	int			j;

	i = 1;
	j = 0;
	while (node->full_cmd[i] && ft_strchr(node->full_cmd[i], '-'))
		i++;
	if (node->full_cmd[i - 1])
	{
		while (node->full_cmd[i - 1][j])
		{
			if (ft_isdigit(node->full_cmd[i - 1][j]))
				return (0);
			j++;
		}
	}
	if (stat(node->full_cmd[i], &file_info) == 0 || !node->full_cmd[i])
		return (1);
	return (0);
}
