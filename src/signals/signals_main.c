/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:45:02 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/19 00:01:42 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	The signal function will have different behaviours
 	depending on from which process it will be invoqued .
 	1) For main process:
 		--> ctrl-c: signal is silenced and prints a newline.
 		--> ctrl-backslash: shouldn't do anything
		
 	2) For child process:
 		--> all signals return to initial values.
 		--> ctrl-c should terminate the program on child process.
 		--> ctrl-backslash should cause SIGQUIT and terminate the program.
	3) For heredoc:
 		--> ctrl-c should terminate the opened child process with input prompt.
 		--> ctrl-backslash shouldn't do anything
		
    Ctrl+C - SIGINT : 2
    Ctrl+\ - SIGQUIT : 3
*/

/*
	The aim of this funtion is that ^C does not 
	get printed while minishell is running in
	main process (interactive).

	tcgetattr(int fildes, struct termios *termios_p);
	We are making 2 copies of the default parameters
	termios (terminal input/ouput). One will be to be manipluated,
	the other one to come back to default settings when needed.
	
	new_settings.c_lflag &= ~ECHOCTL;
	changing the field c_lflag from the structure with bits 
	operations we are avoiding that ^C, appears in the terminal
	
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &new_settings);
	setting the new atributes (~ECHOCTL) after waiting 
	until all queued output has been written and 
	also discards any queued input (TCSAFLUSH).
*/

void	no_print_ctrlc(struct termios *default)
{
	struct termios new_settings;
	
	tcgetattr(STDOUT_FILENO, default);
	tcgetattr(STDOUT_FILENO, new_settings);
	new_settings.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &new_settings);
}

/*
	Reseting parameters to default
*/

void	reset_print_ctrlc(struct termios *default)
{
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, default);
}

/*
 	Behaviour from signals in main process:
 		--> ctrl-c: signal is silenced,no_print_ctrlc, 
		and prints a newline.
 		--> ctrl-backslash: shouldn't do anything
*/

void	signals_main(struct termios *default)
{
	no_print_ctrlc(default);
	sigint_main(); //seguir aqui sabado
	sigquit_main();
}