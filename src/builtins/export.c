/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:45:04 by pguranda          #+#    #+#             */
/*   Updated: 2022/11/08 11:35:35 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isvalid(char* string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (ft_isalnum(string[i]) != 1 || string[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

// CHeck printing with or without = 
int	builtin_export(t_env *envp, char **argv)
{
	t_env	*exported_var;
	char	**key_value;
	char	*eq_p;

	// print_2d(argv);
	key_value = NULL;
	eq_p = NULL;
	if (envp == NULL || argv == NULL)
		return (EXIT_FAILURE);
	if (argv[1] == NULL)
	{
		print_env_lst_export(envp);
		return (EXIT_SUCCESS);
	}
	argv++;
	printf ("%s", *argv);
	// while (argv != NULL)
	// {
	// 	if (ft_isalpha(*argv) != 1 && ft_isvalid(argv) == EXIT_FAILURE)
	// 	{
	// 		printf("minishell: export: %s: not a valid identifier\n", argv);
	// 		continue ;


	
	// while (*argv != NULL)
	// {
	// 	if (ft_strchr(*argv, '=') != NULL)
	// 	{
	// 		eq_p = ft_strchr(*argv, '=');
	// 		if (ft_isalnum(*(eq_p + 1)) == 1)
	// 		{
	// 			key_value = split_into_key_value(*argv);
	// 			if(key_value == NULL || key_value[0] == NULL || key_value[1] == NULL)
	// 				return (EXIT_FAILURE);
	// 			exported_var = ft_lstnew_env(key_value[0], key_value[1]);
	// 			if(exported_var == NULL)
	// 				return (EXIT_FAILURE);
	// 			ft_lstadd_back_mini(&envp, exported_var);
	// 		}
	// 		else
	// 		{
	// 			exported_var = ft_lstnew_env(*argv, NULL);
	// 			if (exported_var == NULL)
	// 				return (EXIT_FAILURE);
	// 			ft_lstadd_back_mini(&envp, exported_var);
	// 		}
	// 	}
	// 	else	
	// 	{
	// 		exported_var = ft_lstnew_env(*argv, NULL);
	// 		if (exported_var == NULL)
	// 			return (EXIT_FAILURE);
	// 		ft_lstadd_back_mini(&envp, exported_var);
	// 	}
	// 	argv++;
	// }
	return (EXIT_SUCCESS);
}
