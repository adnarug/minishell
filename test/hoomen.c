
# include <stdbool.h>
# include <string.h>
# define	NO_QUOTES		0
# define	SINGLE_QUOTES	'\''
# define	DOUBLE_QUOTES	'\"'
# define	DELIMITERS		" \t|<>"


/* sets the quote_modus if quotes are found. 
 * returns true if it changes the quote modus, otherwise returns
 * false. This return value does not matter for the lexing part
 * but it will be useful when you use this function later again in
 * expansion (DO NOT think about expansion right now)
 * */
bool	change_quote_modus(int *current_modus, int quotes_found)
{
	if (*current_modus == NO_QUOTES) //this means we are entering quotes
	{
		*current_modus = quotes_found;
		return (true);
	}
	if (*current_modus == quotes_found) // this means we are closing quotes
	{
		*current_modus = NO_QUOTES;
		return (true);
	} 
	return (false); // we have found double quotes inside of single or vice versa, 
					// nothing changes
}

/* returns true if the user entered a line with unclosed quotes. Otherwise,
 * returns false.
 */
bool	unclosed_quotes(char *line)
{
	int	modus;

	modus = NO_QUOTES;
	while (*line)
	{
		if (*line == SINGLE_QUOTES || *line == DOUBLE_QUOTES)
			change_quote_modus(&modus, *line);
		line++;
	}
	if (modus != NO_QUOTES)
		return (true);
	return (false);
}

/* scans through a word. The word ends when a delimiter is found
 * AND quote_modus is NO_QUOTES at that moment. When a quote is 
 * found, change_quote_modus is called to change the quote modus
 * if necessary (see above)
 * This function returns a pointer to the first char after the
 * end of the word*/
char	*go_through_word(char *s)
{
	int modus;

	modus = NO_QUOTES;
	while (*s)
	{
		if (*s == SINGLE_QUOTES || *s == DOUBLE_QUOTES)
			change_quote_modus(&modus, (int)*s);
		else if (strchr(DELIMITERS, *s) && modus == NO_QUOTES)
			break ;
		s++;
	}
	return (s);
}

char	*parseword(t_lst *tokenlist, char *ptr)
{
	char *start;
	char *end;
	char *word;
	char temp;

	start = ptr;
	end = go_through_word(ptr);
	temp = *end;
	*end = '\0';
	word = ft_strdup(start);
	*end = temp;
	return (end);
}

int main()
{
	char *line;
	char *ptr;
	t_lst *tokenlst;

	line = "mama|< me <mima >>yo 'amo'>> ||<<";
	ptr = line;
	while (*ptr)
	{
		if (*ptr == '\t' || *ptr == ' ')
			ptr++;
		else if (*ptr == '|' || *ptr == '>' || *ptr == '<')
			ptr = parsemeta(tokenlst, ptr); // add a new token to tokenlist, and move pointer to firs char after meta
		else
			ptr = parseword(tokenlst, ptr);
	}
	return (0);
}