/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:17:57 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/13 13:11:22 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*set_prompt(char *minishell_name)
{
	char*	input_name;

	input_name = malloc(sizeof(char)*ft_strlen(minishell_name) + 1);
	if (input_name == NULL)
		return NULL ;//exit segfault?
	ft_strlcpy(input_name, minishell_name, ft_strlen(minishell_name));
	return (input_name);
}

char* get_prompt(t_input *input)
{
	return ((*input).prompt_name);
}