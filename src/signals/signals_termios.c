/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_termios.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:59:00 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/01 10:58:35 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	The aim of this funtion is that ^C does not 
	get printed while minishell is running in
	main process (interactive).

	tcgetattr(int fildes, struct termios *termios_p);
	We are making 2 copies of the default parameters
	termios (terminal input/ouput). One will be to be manipluated,
	the other one to come back to default settings when needed.
	
	new_settings.c_lflag &= ~ECHOCTL;
	with changing the field c_lflag from the structure with bits 
	operations, we are avoiding that ^C, appears in the terminal
	
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &new_settings);
	setting the new atributes (~ECHOCTL) after waiting 
	until all queued output has been written and 
	also discards any queued input (TCSAFLUSH).
*/

void	no_print_ctrlc(struct termios *per_default)
{
	struct termios new_settings;

	printf("signal will not appear\n");
	tcgetattr(STDOUT_FILENO, per_default);// ya lo hemos hecho en la inicializacion. borrar y Verificar cuando todas las senales esten completas
	tcgetattr(STDOUT_FILENO, &new_settings);
	new_settings.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &new_settings);
}

/*
	Reseting parameters to default
*/

void	reset_print_ctrlc(struct termios *per_default)
{
	printf("reseting behaviour\n");
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, per_default);
}
