/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieves- <fnieves-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:13:48 by fnieves-          #+#    #+#             */
/*   Updated: 2022/10/20 18:38:08 by fnieves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
//list
// DEFINE SEPARATORS:
# define SPACE				' '
# define SINGLE_QUOTE		'\''
# define DOUBLE_QUOTE		'\"'
# define DOLLAR				'$'
# define REDIRECT_IN		'<'
# define REDIRECT_OUT		'>'
# define PIPE				'|'
# define SLASH				'/'

//TOKEN FLAGS:
# define T_WORD				1
# define T_REDIRECT_IN		2
# define T_REDIRECT_OUT		3
# define T_APPEND			4
# define T_HEREDOC			5
# define T_PIPE				6

/* My structures */

//token node
typedef struct s_nod_token
{
	char	*name;
	int		flag;
	struct s_nod_token	*next;
	
}	t_nod_token;

//struct header of the token list
typedef struct s_list_token
{
	t_nod_token	*head;
	int	size;
}t_list_token;



void add_toke_list(t_list_token *list, t_nod_token *new);
t_nod_token *create_tok(char *word_tok);
t_nod_token *find_last_node(t_list_token *list);
void	delete_list(t_list_token *list);
void init_list_tok(t_list_token *list);
void	creat_lst_tok(t_list_token *list, char **array_w);

void free_array_list(t_list_token *list, char **array_w);
void	free_array(char **array_w);
void	print_list(t_list_token *list);


//

/*
	Add a new token to the end of the list
*/
void add_toke_list(t_list_token *list, t_nod_token *new)
{
	t_nod_token	*last;
	
	if (!list) //List does not exist >>> return
		return;
	if (!list->head) //Empty list. Add token
	{
		list->head = new;
		return ;
	}
	last = find_last_node(list);
	last->next = new;
}

/*
	We create a node from the each word,
	separated by a space coming from promt.
	If there is any problem in the operation we return,
	a pointer to NULL
	Returns the pointer to the node.
*/
t_nod_token *create_tok(char *word_tok)
{
	t_nod_token *new_tok;
	
	new_tok = (t_nod_token *)malloc(sizeof(t_nod_token));
	if (!new_tok)
		return (NULL);
	new_tok->name = NULL; //do we need to inicializar a null the field word?
	new_tok->next = NULL;
	new_tok->name = ft_strdup(word_tok);
	if (!new_tok->name)
	{
		free(new_tok); //free . despues de free , se iguala new_tok = NULL?
		return (NULL);
	}
	return(new_tok);
}

t_nod_token *find_last_node(t_list_token *list)
{
	t_nod_token	*last;

	if (!list || !list->head)
		return (NULL);
	last = list->head;
	while (last->next)
		last = last->next;
	return (last);
}

void	delete_list(t_list_token *list)
{
	t_nod_token	*del;
	t_nod_token	*current;
	
	if (!list || !list->head)
		return ;
	del = list->head;
	while (del)
	{
		current = del->next;
		free(del->name);
		free(del);
		del = current;
	}
	list->head = NULL;
}



/*
	inicializamos los valores de a lista de tokens
*/
void init_list_tok(t_list_token *list)
{
	list->head = NULL;
	list->size = 0;
}

/*
	From the array separated by spaces, coming from prompt
	we create a node with the char , array[i],
	and add it to the end of the list
*/
void	creat_lst_tok(t_list_token *list, char **array_w)
{
	int i;
	t_nod_token *new;
	
	new = NULL;
	i = 0;
	if(!array_w[i]) // la lista de argumentos esta vacia
	{
		printf("the line is empty. prompt again and free array and list?\n");
		free_array_list(list, array_w);
		return ; //o quuiza es un exit , para poder seguir poiniendo el prompt
	}
	while (array_w[i])
	{
		new = create_tok(array_w[i]);
		if (!new) //si hay algun problema en la creacion del nodo, liberar todo y return
		{
			free_array_list(list, array_w); //es la misma funcion que arriba?
			return ;
		}
		add_toke_list(list, new); //vamos a pasar a lista
		i++;
		//si hay algun probema, hacer un free, de toda la lista
	}
	free_array(array_w);
}


void	ft_parser(t_list_token *list, char *line)
{
	//t_list_token list; // pasamos esto &*
	char	**array_w;

	array_w = NULL;
	array_w = ft_split((const char*)line, SPACE);
	init_list_tok(list);
	creat_lst_tok(list, array_w);
	printf("imprime linea en programa: %s\n", line);
}

void	free_array(char **array_w)
{
	int i;

	i = -1;
	while (array_w[++i])
	{
		free(array_w[i]);
	}
	free(array_w);
}

void free_array_list(t_list_token *list, char **array_w)
{
	free_array(array_w);
	delete_list(list);
}


void	check_leaks(void)
{
	system("leaks parser");
}


int main(int argc, char **argv)
{
	t_list_token	list;
	
	if (argc != 2)
	{
		printf("numero de parametros incorrecto. Pon entre comillas\n");
		return(0);
	}
	ft_parser(&list, argv[1]);
	atexit(check_leaks);
	print_list(&list);
	delete_list(&list);
	
	return (1);
}


//printitin list felipe . to be deleted
void	print_list(t_list_token *list)
{
	t_nod_token	*temp;
	int i = 0;
	if (!list)
	{
		printf("List does not exist which does not mean is leer\n");
		return;
	}
	if (!list->head)
	{
		printf("List exists but with no nodes\n");
		return;
	}
	temp = list->head;
	printf("-------Informacion de La lista----------\n");
	while(temp)
	{
		printf("Elemnto: %i, valor= %s, tipo = %i \n",i ,temp->name, temp->flag);
		i++;
		temp = temp->next;
	}
	printf("-------END  IMPRESION  lista-------\n");
}