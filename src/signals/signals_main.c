/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:45:02 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/01 10:37:12 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*

	rl_on_new_line();
	show new prompt and take new  input (prebuild function)
	
	void rl_replace_line (const char *texto1, int clear_undo)
	Replace the contents of rl_line_buffer with texto1 (*1)

	void rl_redisplay (void)
	Change what’s displayed on the screen
	to reflect the current contents of rl_line_buffer

	(*1)Problems with rl_replace_line (from SLack)
	brew link --force readline  
	or: brew unlink readline && brew link --force readline
	export C_INCLUDE_PATH="$HOME/.brew/include:$C_INCLUDE_PATH"
	export LIBRARY_PATH="$HOME/.brew/lib:$LIBRARY_PATH"
	
	For testing: a.out >>> es un child
	Heredoc : create a heredoc, for a father
*/

void	new_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
	glob_var_exit = 1;
}

void	sigquit_main()
{
	struct sigaction	sigac;

	sigac.sa_handler = SIG_IGN;
	sigemptyset(&sigac.sa_mask);
	sigac.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sigac, NULL);
}

/*
	https://www.youtube.com/watch?v=_1TuZUbCnX0
	sa_mask = set of signals to be ignored during 
	execution of &hanlder. If we do not use sigprocmask function
	to mask/unmask more signals and their behaviour, we should not take it
	into account, so we use sigemptyset(&sigac.sa_mask). Also blocks the signal
	which already triggered  &hanlder (SIGINT)
	SA_RESTART = Automatically restart interrupted
	system calls. Will run  all the lines before from sigint_main().
	sigaction(SIGINT, &sigac, NULL) -> it does the bussines
*/

void	sigint_main()
{
	struct sigaction	sigac;

	sigac.sa_handler = &new_prompt;
	sigemptyset(&sigac.sa_mask);
	sigac.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sigac, NULL);
}

/*
 	Behaviour from signals in main process:
 		--> Ctrl+C - SIGINT (int 2): signal is silenced, no_print_ctrlc, 
		and prints a newline.
 		--> Ctrl+\ - SIGQUIT (int 3): shouldn't do anything
	
	Ctrl+D : is not a signal, but the sending of EOF.
	For readline() it is equivalent to a NULL, if it is sent in an empty prompt.
	If there is something written at the prompt, it does nothing because
	by default, at the end of the written line there is already an EOF
	that is unique (therefore we can not add another EOF).
	In brief nothing extra happens. Ctrl+D will be managed in main.c
*/

void	signals_main(struct termios *per_default)
{
	no_print_ctrlc(per_default);
	sigint_main(); //seguir aqui sabado
	sigquit_main();
}