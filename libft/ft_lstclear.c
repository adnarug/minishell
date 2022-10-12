/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:38:00 by pguranda          #+#    #+#             */
/*   Updated: 2022/04/21 16:34:49 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list				*curr;
	t_list				*temp;

	curr = *lst;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr -> next;
		ft_lstdelone(temp, del);
	}
	*lst = NULL;
}
