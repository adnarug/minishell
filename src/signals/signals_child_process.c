/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:06:36 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/10 14:48:22 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Both functions, sigint_child() and sigquit_child(), 
	will return the default parameters with "sigac.sa_handler = SIG_DFL;"
	to the signals we have changed in 
	void	signals_main(struct termios *per_default)
	which are those desired by the exercise.
*/

void	sigint_child(void)
{
	struct sigaction	sigac;

	sigac.sa_handler = SIG_DFL;
	sigac.sa_flags = SA_RESTART;
	sigemptyset(&sigac.sa_mask);
	sigaction(SIGINT, &sigac, NULL);
}

void	sigquit_child(void)
{
	struct sigaction	sigac;

	sigac.sa_handler = SIG_DFL;
	sigac.sa_flags = SA_RESTART;
	sigemptyset(&sigac.sa_mask);
	sigaction(SIGQUIT, &sigac, NULL);
}

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

void	signals_child_process(struct termios *per_default)
{
	reset_print_ctrlc(per_default);
	sigint_child();
	sigquit_child();
}

void	signals_heredoc_process(void)
{
	sigint_child();
	sigquit_parent();
}
