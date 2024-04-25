/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:09:24 by etornay-          #+#    #+#             */
/*   Updated: 2023/05/04 15:17:36 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*aux;

	if (!lst)
	{
		return ;
	}
	while (*lst)
	{
		aux = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = aux;
	}
	*lst = 0;
	return ;
}

/* (*del)((*lst)->content);
free(*lst);

Puede sustituirse por:

ft_lstdelone(*lst, del); */