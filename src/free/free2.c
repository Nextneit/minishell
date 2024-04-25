/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:09:40 by ncruz-ga          #+#    #+#             */
/*   Updated: 2024/03/14 16:29:19 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_cmd(t_list **lst)
{
	free(((t_parser *)((*lst)->content))->full_cmd);
	((t_parser *)((*lst)->content))->full_cmd = NULL;
	free(((t_parser *)((*lst)->content))->full_path);
	((t_parser *)((*lst)->content))->full_path = NULL;
	if (((t_parser *)((*lst)->content))->infile != 0)
		close(((t_parser *)((*lst)->content))->infile);
	if (((t_parser *)((*lst)->content))->outfile != 1)
		close(((t_parser *)((*lst)->content))->outfile);
	free(((t_parser *)((*lst)->content)));
}

void	free_cmd_list(t_list **lst)
{
	t_list	*aux;
	int		i;

	if (!*lst)
		return ;
	while (*lst)
	{
		aux = (*lst)->next;
		i = -1;
		if (((t_parser *)((*lst)->content))->full_cmd)
		{
			while (((t_parser *)((*lst)->content))->full_cmd[++i])
			{
				free(((t_parser *)((*lst)->content))->full_cmd[i]);
				((t_parser *)((*lst)->content))->full_cmd[i] = NULL;
			}
		}
		free_cmd(lst);
		free((*lst));
		*lst = aux;
	}
	*lst = NULL;
}

void	free_lex2(t_data *p)
{
	int	i;

	i = 0;
	if (p->lex2 != NULL)
	{
		while (p->lex2[i])
		{
			free(p->lex2[i]);
			p->lex2[i++] = NULL;
		}
		free(p->lex2);
		p->lex2 = NULL;
	}
}

void	free_split(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free (tmp);
}

void	free_cd_error(t_data *p)
{
	free(p->tmp);
	free(p->cd_error);
	g_status = 1;
}
