/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:52:40 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/10 18:57:08 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	real_env(t_minishell *data)
{
	t_env	*tmp;

	tmp = data->env_lst;
	while (tmp)
	{
		if (tmp->key[0])
		{
			if (ft_strlen(tmp->value) != 0)
				printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			else if (ft_strchr(tmp->value, '=') == NULL)
				printf("declare -x %s\n", tmp->key);
			else if (ft_strchr(tmp->value, '=') != NULL)
				printf("declare -x %s=\"\"\n", tmp->key);
		}
		tmp = tmp->next;
	}
}

static int	correct_key(char *s)
{
	int	i;

	i = 1;
	if (!s || ft_strlen(s) < 1)
		return (0);
	if (s[0] != '_' && !ft_isalpha(s[0]))
		return (0);
	while (s[i])
	{
		if ((s[i] == '=' && i != 0) || (s[i] == '+' \
		&& s[i + 1] && s[i + 1] == '=' && i != 0))
			return (1);
		else if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) \
		&& s[i] != '_' && i != 0)
			return (0);
		i++;
	}
	return (1);
}

char	*create_key(char *s, int *i, t_minishell *data)
{
	char	*key;

	key = NULL;
	if (!correct_key(s))
		return (key);
	while (s[*i])
	{
		if (s[*i] == '=' || s[*i] == '+')
			break ;
		(*i)++;
	}
	key = malloc(sizeof(char) * ((*i) + 1));
	if (key == NULL)
		print_error_free_exit(data, MALLOC_ERR, MALLOC_ERR_NO, true);
	key[(*i)] = '\0';
	*i = 0;
	while (s[(*i)])
	{
		if (s[(*i)] == '=' || s[*i] == '+')
			break ;
		key[(*i)] = s[(*i)];
		(*i)++;
	}
	return (key);
}
