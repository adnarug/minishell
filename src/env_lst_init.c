/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:19:20 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/17 13:33:07 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Creating and filling l_env based on a copy of envp */
t_env	*ft_initializer(char **dup_env)
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
	env_params_new->next = NULL;
	return (env_params_first);
}

t_env	*ft_node_init(char *envp)
{
	char	*equal_point;
	char	*key;
	char	*value;
	t_env	*head_env;
	int		i;

	i = 0;
	equal_point = NULL;
	value = NULL;
	if (envp == NULL)
		return (NULL);//exit code 
	if (ft_strchr(envp, '=') != 0)
	{
		equal_point = ft_strchr(envp, '=');
		equal_point++;
		key = ft_copy_key(envp);
		head_env = ft_lstnew_env(equal_point, key);
		free (value);
		value = NULL;
	}

	return (head_env);
}

char	*ft_copy_key(char *string)
{
	char	*key;
	int		i;
	int		counter;
	int		len;

	key = NULL;
	i = 0;
	counter = 0;
	len = 0;
	if (ft_strchr(string, '=') == 0)
	{
		printf("Error in finding the = initialize.c/ft_cpy_til_eq");
		return (NULL);
	}
	while (string[len] != '=')
		len++;
	key  = malloc(sizeof (char) * len + 1);
	while (string[i] != '=')
	{
		key[i] = string[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}