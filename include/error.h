/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:33:33 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/02 20:38:42 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
#define ERROR_H

/* Error messages*/
#define ERROR_PRINTED 	"exit\n"
#define ERROR_QUOT 		"quote(s) not closed\n"

# define MALLOC_ERR "Failed at allocating memory.\n"
# define MALLOC_ERR_NO 12

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