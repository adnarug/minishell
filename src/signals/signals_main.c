/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:45:02 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/15 13:49:52 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	press_ctrl_c(int signal_number)
{
	(void)signal_number;
	
}

/*
	The signal function will have different behaviours
 	depending on from which process it will be invoqued .
 	1) For main process:
 		--> ctrl-c: signal is silenced and prints a newline.
 		--> ctrl-backslash: shouldn't do anything
		--> ctrl-d: exits and out of the programm >>> Roman not included???
		
 	2) For child process:
 		--> all signals return to initial values.
 		--> ctrl-c should terminate the program on child process.
 		--> ctrl-backslash should cause SIGQUIT and terminate the program.
	3) For heredoc:
 		--> ctrl-c should terminate the opened child process with input prompt.
 		--> ctrl-backslash shouldn't do anything
*/

void	signals_execut(int process)
{
	if (process == MAIN)
	{
		signal(SIGINT, &press_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
}