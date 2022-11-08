/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:54:13 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/08 10:58:59 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//printitin list felipe . to be deleted
void	print_list(t_list_token *list)
{
	t_nod_token	*temp;
	int i = 0;
	if (!list)
	{
		printf("List does not exist which does not mean is leer\n");
		return;
	}
	if (!list->head)
	{
		printf("List exists but with no nodes\n");
		return;
	}
	temp = list->head;
	printf("-------Informacion de La lista----------\n");
	while(temp)
	{
		if (temp->quote)
			printf("Elemnto: %i, valor= %s, tipo = %c,  quote ON =%c \n",i ,temp->name, temp->flag, temp->quote);
		// else if (temp->double_quote)
		// 	printf("Elemnto: %i, valor= %s, tipo = %c, double quot ON =%i \n",i ,temp->name, temp->flag, temp->double_quote);
		else
			printf("Elemnto: %i, valor= %s, tipo = %c. No single/double quote \n",i ,temp->name, temp->flag);
		i++;
		temp = temp->next;
	}
	printf("-------END  IMPRESION  lista-------\n");
}

void print_token(t_nod_token	*token)
{
	if (!token)
	{
		printf("token apunta  anull\n");
		return;
	}
	printf("-------imprimirmpos valores det oken----------\n");
	printf("el valor de name: %s\n", token->name);
	printf("-------END  IMPRESION  TOKEN-------\n");

}