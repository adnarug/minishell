/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:06:36 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/19 19:26:07 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 	We have to reset termios
	For child process:
 		--> all signals return to initial values.
 		--> ctrl-c should terminate the program on child process.
 		--> ctrl-backslash should cause SIGQUIT and terminate the program.
	
	For heredoc:
 		--> ctrl-c should terminate the opened child process with input prompt.
 		--> ctrl-backslash shouldn't do anything
*/
