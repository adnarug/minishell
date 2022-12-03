/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:19:20 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/03 17:47:02 by fnieves-         ###   ########.fr       */
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
//TODO: Can be potentially merged with the export init function
t_env	*ft_node_init(char *envp)
{
	char	*equal_point;
	char	*key;
	t_env	*head_env;
	int		i;

	i = 0;
	equal_point = NULL;
	if (envp == NULL)
		return (NULL);// exit code 
	if (ft_strchr(envp, '=') != 0)
	{
		equal_point = ft_strchr(envp, '=');
		equal_point++;
		key = ft_copy_key(envp);
		head_env = ft_lstnew_env(key, equal_point);
		return (head_env);
	}
	else
		return (NULL);
}
/*TODO: add the checks for the missing value. 
This function splits "KEY=VALUE", into key_value[0] = KEY, key_value[1] = VALUE, key_value[2] = NULL;*/
char **split_into_key_value(char *string)
{
	char	**key_value;
	char	*value;
	int		i;
	int		len;

	i = 1;
	len = 0;
	value = NULL;
	if (string == NULL)
		return (NULL);
	while (string[i] != '=')
		i++;
	value = ft_strchr(string, '=');
	key_value = malloc(sizeof(char *) * 3);
	key_value[0] = malloc(sizeof(char)* i + 1);
    value++;
	key_value[1] = ft_strdup(value);
	if (key_value == NULL || key_value[0] == NULL || key_value[1] == NULL)
		return (NULL); 
	while (i > 0)
	{
		key_value[0][len] = string[len];
		len++;
		i--;
	}
    key_value[2] = NULL;
	return (key_value);
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