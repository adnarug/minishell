/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_parent_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves <fnieves@42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:49:08 by fnieves-          #+#    #+#             */
/*   Updated: 2022/12/10 14:48:53 by fnieves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_parent(void)
{
	struct sigaction	sigac;

	sigac.sa_handler = SIG_IGN;
	sigemptyset(&sigac.sa_mask);
	sigac.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sigac, NULL);
}

void	sigquit_parent(void)
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

void	signals_parent_process(void)
{
	sigint_parent();
	sigquit_parent();
}
