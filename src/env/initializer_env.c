/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:16:38 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/10 18:40:08 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Creating and filling l_env based on a copy of envp */
t_env	*create_env_lst(char **dup_env)
{
	int		i;
	t_env	*env_params_previous;
	t_env	*env_params_new;
	t_env	*env_params_first;

	i = 0;
	env_params_first = ft_node_init(dup_env[i]);
	env_params_previous = env_params_first;
	i++;
	while (dup_env[i] != NULL)
	{
		env_params_new = ft_node_init(dup_env[i]);
		ft_lstadd_back_mini(&env_params_previous, env_params_new);
		env_params_previous = env_params_new;
		i++;
	}
	env_params_previous->next = NULL;
	return (env_params_first);
}

char	*ft_copy_key(char *string)
{
	char	*key;
	int		i;
	int		len;

	key = NULL;
	len = 0;
	i = 0;
	if (ft_strchr(string, '=') == 0)
		return (NULL);
	while (string[len] != '=')
		len++;
	key = malloc(sizeof(char) * (len + 1));
	if (key == NULL)
		return (NULL);
	while (string[i] != '=')
	{
		key[i] = string[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

/*Making a copy of equal sign and value e.g. "=pguranda"*/
char	*ft_copy_eq_value(char *string)
{
	char	*value;
	int		i;
	int		len;

	value = NULL;
	len = 0;
	i = 0;
	while (*string != '=' && *string != '\0')
		string++;
	string++;
	len++;
	while (string[len] != '\0')
		len++;
	value = malloc(sizeof(char) * len + 1);
	if (value == NULL)
		return (NULL);
	while (string[i] != '\0')
	{
		value[i] = string[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

t_env	*ft_node_init(char *envp)
{
	char	*eq_value;
	char	*key;
	t_env	*head_env;
	int		i;

	i = 0;
	if (envp == NULL)
		return (NULL);
	if (ft_strchr(envp, '=') != 0)
	{
		key = ft_copy_key(envp);
		eq_value = ft_copy_eq_value(envp);
		head_env = ft_lstnew_env(key, eq_value);
		return (head_env);
	}
	else
		return (NULL);
}
