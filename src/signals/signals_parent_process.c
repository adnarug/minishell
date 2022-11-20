/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_parent_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:49:08 by fnieves-          #+#    #+#             */
/*   Updated: 2022/11/20 20:31:34 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_parent()
{
	struct sigaction	sigac;

	sigac.sa_handler = SIG_IGN;
	sigemptyset(&sigac.sa_mask);
	sigac.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sigac, NULL);
}

void	sigquit_parent()
{
	struct sigaction	sigac;

	sigac.sa_handler = SIG_IGN;
	sigemptyset(&sigac.sa_mask);
	sigac.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sigac, NULL);
}

/*
	For parent process:
		--> Both signals, ctrl-c and ctrl-\ will 
		be ignored.
*/

void	signals_parent_process(struct termios *per_default)
{
	sigint_parent();
	sigquit_parent();
}
