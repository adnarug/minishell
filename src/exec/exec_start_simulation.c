/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:43:12 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/23 15:59:18 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_prs_tok *iter_until_cmd(t_header_prs_tok *header)
{
	while (header != NULL)
	{
		while(header->tokens != NULL)
		{
			if (header->tokens->type == 'c')
				return (header->tokens);
			header->tokens = header->tokens->next;
		}
		header = header->next;
	}
}
