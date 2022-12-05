/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:52:40 by pguranda          #+#    #+#             */
/*   Updated: 2022/12/05 16:40:49 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static char	*make_val(char *s, int i, int plus)
// {
// 	char	*val;

// 	val = NULL;
// 	if (s[i] != '\0' && s[i + 1] != '\0' && !plus)
// 		val = ft_strdup(s + i + 1);
// 	else if (s[i] != '\0' && s[i + 1] != '\0' && plus)
// 	{
// 		i++;
// 		if (s[i] != '\0' && s[i + 1] != '\0')
// 			val = ft_strdup(s + i + 1);
// 	}
// 	if (val == NULL)
// 		val = ft_strdup("");
// 	return (val);
// }

// static void	old_key(t_env *new, char *val, char *key, int plus)
// {
// 	if (new->equal == 0)
// 	{
// 		free(key);
// 		free(val);
// 		return ;
// 	}
// 	free(key);
// 	if (plus)
// 	{
// 		new->val = ft_strjoin(new->val, val);
// 		free(val);
// 		return ;
// 	}
// 	free(new->val);
// 	new->val = val;
// }

// static void	make_envp(char *s, t_minishell *data, int plus)
// {
// 	char	*key;
// 	char	*val;
// 	int		i;
// 	t_env	*new;
// 	t_env	*list;

// 	val = NULL;
// 	list = data->env_lst
// 	i = 0;
// 	key = make_key(s, &i);
// 	if (key == NULL)
// 		return ;
// 	new = ft_lst_find(data->env_lst, key);
// 	val = make_val(s, i, plus);
// 	// if (new != NULL)
// 	// {
// 	// 	new->equal = ft_haschar(s, '=');
// 	// 	old_key(new, val, key, plus);
// 	// }
// 	// else
// 	// {
// 	// 	new = ft_new_envp(key, val);
// 	// 	new->equal = ft_haschar(s, '=');
// 	// 	ft_add_envp_back(&list, new);
// 	// }
// }

void	true_env(t_minishell *data)
{
	t_env	*tmp;

	tmp = data->env_lst;
	while (tmp)
	{
		if (tmp->key[0])
		{
			if (ft_strlen(tmp->value) != 0)
				printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			else if (ft_strchr(tmp->value,'=') == NULL)
				printf("declare -x %s\n", tmp->key);
			else if (ft_strchr(tmp->value,'=') != NULL)
				printf("declare -x %s=\"\"\n", tmp->key);
		}
		tmp = tmp->next;
	}
}

static int	true_key(char *s)
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

char	*make_key(char *s, int *i)
{
	char	*key;

	key = NULL;
	if (!true_key(s))
		return (key);
	while (s[*i])
	{
		if (s[*i] == '=' || s[*i] == '+')
			break ;
		(*i)++;
	}
	key = malloc(sizeof(char) * ((*i) + 1));
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
