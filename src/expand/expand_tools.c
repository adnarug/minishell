/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:33:32 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/09 13:02:08 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Return true if find the char which does not 
	finish the expansion var $ (a-Z, 0-9 or _)
*/

int is_not_end_expand(char c)
{
	//printf("not expand 1\n");

	return(ft_isalpha(c) ||  c == '_' || ft_isdigit(c));
}


//X$USER0$HOME