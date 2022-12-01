/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:33:33 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/01 15:39:50 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
#define ERROR_H

/* Error messages*/
#define ERROR_PRINTED 	"error\n"
#define ERROR_QUOT 		"quote(s) not closed\n"


/* Error return values */
# define QUOTE_MISSING		1

#endif


/*
bash-3.2$ Echo >> $HOME1 
bash: $HOME1: ambiguous redirect
bash-3.2$ >>
bash: syntax error near unexpected token `newline'
bash-3.2$ >> $HOME1
bash: $HOME1: ambiguous redirect
bash-3.2$ 
	echo text"'$USER'" ' $USER '   '"'$USER'"' grep hi -l >> '$USER' | wc -w >> $HOME | echo > $?? 
*/