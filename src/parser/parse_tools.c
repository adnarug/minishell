/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:21:15 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/24 19:21:27 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


t_prs_tok *find_last_parsedtok_sublist(t_header_prs_tok *sub_list_pars)
{
	t_prs_tok *last;
	
	if (!sub_list_pars)
	{
		printf("sublist does not exit, something wrong is happening\n");
		return (NULL);
	}
	last = sub_list_pars->next;
	while (last)
	{
		last = last->next;
	}
	return (last);
}