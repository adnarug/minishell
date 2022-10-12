/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:10:00 by pguranda          #+#    #+#             */
/*   Updated: 2022/04/14 11:53:02 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list				*new_lst;
	t_list				*new_node;
	t_list				*curr;

	new_lst = NULL;
	curr = lst;
	while (curr != NULL)
	{
		new_node = ft_lstnew(f(curr->content));
		if (new_node != NULL)
			ft_lstadd_back(&new_lst, new_node);
		else
		{
			ft_lstclear (&new_lst, del);
			return (NULL);
		}
		curr = curr -> next;
	}
	return (new_lst);
}
