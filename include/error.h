/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:33:33 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/13 23:26:01 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/* Error messages*/
# define ERROR_PRINTED	"exit\n"
# define QUOTE_ERR		"quote(s) not closed\n"
# define REDIR_EMPTY	"minishell: syntax error near unexpected \
token`newline'\n"
# define REDIR_EXPAND_EMPTY		"minishell : ambiguous redirect\n"

# define MALLOC_ERR "Failed at allocating memory.\n"
# define MALLOC_ERR_NO 12
# define CMD_NOT_FOUND 127 
# define EXIT_NUM_ARG 255
# define INVALID_EXIT_ARG 255
# define INVALID_ARG 1
# define EXPORT_ERROR				8
# define INVAL_UNS	18
# define INVAL_EXP	17
# define NO_FILE_OR_DIR 17

/* Error return values */
# define QUOTE_ERR_NO		1
# define REDIR_EMPTY_NO		2
# define REDIR_EXPAND_EMPTY_NO	1

#endif