/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:14:39 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/02 18:16:05 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Launches a child process to our minishell. 
To check - CTRL + T - Activity Monitor, and search for infinite_file and/or minishell - should be found with different PIDS*/

int main(void)
{
    while (1)
    {
        printf("imprimo y epsero\n");
        sleep (4);
    }
}