/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:19:20 by pguranda          #+#    #+#             */
/*   Updated: 2022/10/15 18:24:05 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_initializer(char **envp)
{
	/*
	1. search for =
	2. +1 until the end is the value
	3. from the beginning until the point is the key
	4.start the list and iterate through it, add NULL at the end
	*/
	t_env	*env_params_head;
	t_env	*env_params_new;
	t_env	*env_params_first;
	char	**dup_env;
	int		i;

	i = 0;
	dup_env = dup_matrix(envp);
	env_params_head = ft_head_initializer(dup_env[i]);
	env_params_first = env_params_head;
	i++;
	while (dup_env[i] != NULL)
	{
		env_params_new = ft_head_initializer(dup_env[i]);
		ft_lstadd_back_mini(&env_params_head, env_params_new);
		env_params_head = env_params_new;
		i++;
	}
	env_params_new->next = NULL;
	// ft_lstadd_back_mini(&env_params_head, NULL);
	// print_env_lst(env_params_head);
	return (env_params_head);
}

/*Copying the */
t_env	*ft_head_initializer(char *envp)
{
	char	*equal_point;
	t_env	*head_env;
	int		i;

	i = 0;
	equal_point = NULL;
	if (envp == NULL)
		return (NULL);//exit code 
	// printf("%s", envp);
	if (ft_strchr(envp, '=') != 0)
	{
		equal_point = ft_strchr(envp, '='); 
		head_env = ft_lstnew_env(equal_point, ft_cpy_till_eq(envp));
		// printf("%s", equal_point);
		// printf("%s", ft_cpy_till_eq(envp));
		// print_env_lst(head_env);
	}
	return (head_env);
}

char	*ft_cpy_till_eq(char *string)
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
	// printf("key %s", key);
	return (key);
}