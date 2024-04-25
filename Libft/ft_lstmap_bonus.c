/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etornay- <etornay-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:45:28 by etornay-          #+#    #+#             */
/*   Updated: 2023/05/08 18:05:17 by etornay-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*elem;
	void	*aux;

	if (!lst)
		return (0);
	new = 0;
	while (lst)
	{
		aux = f(lst->content);
		elem = ft_lstnew(aux);
		if (elem)
		{
			ft_lstadd_back(&new, elem);
			lst = lst->next;
		}
		else
		{
			ft_lstclear(&new, del);
			del(aux);
			return (0);
		}
	}
	return (new);
}
