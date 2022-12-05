/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:22:55 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/05 12:21:12 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void my_strerror(char *err_cmd, int err_num)
{
	if (err_num == CMD_NOT_FOUND)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(err_cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
		if (err_num == EXIT_NUM_ARG)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(err_cmd, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
}

void cmd_str_error(char *err_cmd, char *err_msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err_cmd, 2);
	ft_putstr_fd(err_msg, 2);
}