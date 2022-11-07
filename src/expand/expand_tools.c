/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:33:32 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/07 17:58:55 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Return true if find the char which does not 
	finish the expansion var $ (a-Z, 0-9 or _)
*/
/// @brief true if char is not end of var $ expasion
/// @param c char  to check
/// @return true if noot end of expansion
int not_end_expand(char c)
{
	return(ft_isalpha(c) ||  c == '_');
}
