/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:45:04 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/05 17:03:40 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// /* checks if argument for export is valid. Before the '=' sign, only
//  * alphanumerical characters and underscores are permitted. After the equal
//  * sign, all ascii-chars are permitted. If the length of s is size_t max or
//  * bigger, returns false.
//  */
// bool	ft_is_valid(char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!first_char_valid(s[i]))
// 		return (false);
// 	i = 0;
// 	while (s[i] && s[i] != '=')
// 	{
// 		if (!ft_isalnum(s[i]) && s[i] != '_')
// 			return (false);
// 		i++;
// 		if (i == (size_t) - 1)
// 			return (false);
// 	}
// 	return (true);
// }

// void	mini_export_invalid_identifier(char *arg)
// {
// 	// print_error("export", arg, NULL, -1);
// 	ft_putstr_fd("not a valid identifier\n", 2);
// 	glob_var_exit = 1;
// }

// static void	key_export(t_minishell *data)
// {
// 	int	i;
// 	int	plus;

// 	plus = 0;
// 	i = 1;
// 	while (data->exec->cmd_flags[i] != NULL)
// 	{
// 		// if (ft_haschar((*data)->exec->cmd[i], '+') && \
// 		// ft_check_plus((*data)->exec->cmd[i]))
// 		// 	plus = 1;
// 		//add the element
// 		i++;
// 		plus = 0;
// 	}
// }

// // CHeck printing with or without = 
// int	builtin_export(t_minishell *data)
// {
// 	t_env	*exported_var;
// 	char	**key_value;
// 	char	*eq_p;
// 	int		i;

// 	// print_2d(argv);
// 	key_value = NULL;
// 	eq_p = NULL;
// 	(void)exported_var;
// 	i = 0;
// 	if (data->env_lst == NULL || data->exec->cmd_flags == NULL)
// 		return (EXIT_FAILURE);
// 	if (data->exec->cmd_flags[1] == NULL)
// 	{
// 		print_env_lst_export(data->env_lst);
// 		return (EXIT_SUCCESS);
// 	}
// 	i++;
// 	while (data->exec->cmd_flags[i] != NULL)
// 	{
// 		if (is_valid(data->exec->cmd_flags[i]) == true)
// 		{
// 			if (ft_is_valid(data->exec->cmd_flags[i] == true)
// 				key_export(data);
// 			else
// 				mini_export_invalid_identifier(data->exec->cmd_flags[i]);
// 			i++;
// 		}
// 	}

// 	// while (argv != NULL)
// 	// {
// 	// 	if (ft_isalpha(*argv) != 1 && ft_isvalid(argv) == EXIT_FAILURE)
// 	// 	{
// 	// 		printf("minishell: export: %s: not a valid identifier\n", argv);
// 	// 		continue ;

// 	// while (*argv != NULL)
// 	// {
// 	// 	if (ft_strchr(*argv, '=') != NULL)
// 	// 	{
// 	// 		eq_p = ft_strchr(*argv, '=');
// 	// 		if (ft_isalnum(*(eq_p + 1)) == 1)
// 	// 		{
// 	// 			key_value = split_into_key_value(*argv);
// 	// 			if(key_value == NULL || key_value[0] == NULL || key_value[1] == NULL)
// 	// 				return (EXIT_FAILURE);
// 	// 			exported_var = ft_lstnew_env(key_value[0], key_value[1]);
// 	// 			if(exported_var == NULL)
// 	// 				return (EXIT_FAILURE);
// 	// 			ft_lstadd_back_mini(&envp, exported_var);
// 	// 		}
// 	// 		else
// 	// 		{
// 	// 			exported_var = ft_lstnew_env(*argv, NULL);
// 	// 			if (exported_var == NULL)
// 	// 				return (EXIT_FAILURE);
// 	// 			ft_lstadd_back_mini(&envp, exported_var);
// 	// 		}
// 	// 	}
// 	// 	else	
// 	// 	{
// 	// 		exported_var = ft_lstnew_env(*argv, NULL);
// 	// 		if (exported_var == NULL)
// 	// 			return (EXIT_FAILURE);
// 	// 		ft_lstadd_back_mini(&envp, exported_var);
// 	// 	}
// 	// 	argv++;
// 	// }
// 	return (EXIT_SUCCESS);
// }

static char	*make_val(char *s, int i, int plus)
{
	char	*val;

	val = NULL;
	if (s[i] != '\0' && s[i + 1] != '\0' && !plus)
		val = ft_strdup(s + i + 1);
	else if (s[i] != '\0' && s[i + 1] != '\0' && plus)
	{
		i++;
		if (s[i] != '\0' && s[i + 1] != '\0')
			val = ft_strdup(s + i + 1);
	}
	if (val == NULL)
		val = ft_strdup("");
	return (val);
}

static void	old_key(t_env *new, char *val, char *key, int plus)
{
	if (new->equal == 0)
	{
		free(key);
		free(val);
		return ;
	}
	free(key);
	if (plus)
	{
		new->value = ft_strjoin(new->value, val);
		free(val);
		return ;
	}
	free(new->value);
	new->value = val;
}

static void	make_envp(char *s, t_minishell *data, int plus)
{
	char	*key;
	char	*val;
	int		i;
	t_env	*new;
	t_env	*list;

	val = NULL;
	list = data->env_lst;
	i = 0;
	key = make_key(s, &i);
	if (key == NULL)
		return ;
	printf("before find\n");
	new = ft_lst_find(data->env_lst, key);
	printf("after find\n");
	val = make_val(s, i, plus);
	if (new != NULL)
	{
		new->equal = ft_strchr(s, '=');
		old_key(new, val, key, plus);
	}
	else
	{
		new = ft_lstnew_env(key, val);
		new->equal = ft_strchr(s, '=');
		ft_lstadd_back_mini(&list, new);
	}
}

static void	key_export(t_minishell **data)
{
	int	i;
	int	plus;

	plus = 0;
	i = 1;
	while ((*data)->exec->cmd_flags[i])
	{
		if (ft_strchr((*data)->exec->cmd_flags[i], '+') != NULL) //took out one check
			plus = 1;
		make_envp((*data)->exec->cmd_flags[i], *data, plus);
		i++;
		plus = 0;
	}
}

/*
"export"
export without args will print the whole ENVP list 

"export %s=%s\n", <name>, <value>
exports a new <name> and optional its <value> 
or change an <value> of an old_<name>

"export %s+=%s\n", <name>, <value>
export <name>+=<value> 
will add new_<value> behind the old_<value> of that <name>

its saved in ENVP list then
*/


int	builtin_export(t_minishell *data)
{
	int	ret;

	ret = 1;
	if (!data->exec->cmd_flags[1])
		true_env(data);
	// ret = check_keys(data->exec->cmd_flags, EXPORT_ERROR);
	key_export(&data);
	if (ret != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
