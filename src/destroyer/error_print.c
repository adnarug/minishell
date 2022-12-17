/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:22:55 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/13 22:57:46 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	my_strerror(char *err_cmd, int err_num)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err_cmd, 2);
	if (err_num == CMD_NOT_FOUND)
		ft_putstr_fd(": command not found\n", 2);
	if (err_num == EXIT_NUM_ARG)
		ft_putstr_fd(": numeric argument required\n", 2);
	if (err_num == NO_FILE_OR_DIR)
		ft_putstr_fd(": No such file or directory\n", 2);
}

void	strerr_unset(char *err_cmd, char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err_cmd, 2);
	write(2, "`", 1);
	ft_putstr_fd(s, 2);
	write(2, "'", 1);
	ft_putstr_fd(": not an identifier\n", 2);
}

void	strerr_export(char *err_cmd, int err_num, char *s)
{
	if (err_num == INVAL_EXP)
	{
		ft_putstr_fd(err_cmd, 2);
		ft_putstr_fd(": not an identifier: ", 2);
		ft_putstr_fd(s, 2);
		write(2, "\n", 1);
	}
}

void	cmd_str_error(char *err_cmd, char *err_msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err_cmd, 2);
	ft_putstr_fd(err_msg, 2);
}

void	cmd_str_access(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}
