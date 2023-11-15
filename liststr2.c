#include "shell.hhh"

/**
 * list_length - determines length of linked list
 * @hhh: pointer to first noda
 *
 * Return: size of list
 */
size_t list_length(const list_t *hhh)
{
	size_t i = 0;

	while (hhh)
	{
		hhh = hhh->next;
		i++;
	}
	return (i);
}

/**
 * lista_to_strings - returns an array of strings of the list->str
 * @ras: pointer to first noda
 *
 * Return: array of strings
 */
char **lista_to_strings(list_t *ras)
{
	list_t *noda = ras;
	size_t i = list_length(ras), j;
	char **strs;
	char *str;

	if (!ras || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; noda; noda = noda->next, i++)
	{
		str = malloc(_strlen(noda->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, noda->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_lista - prints all elements of a list_t linked list
 * @hhh: pointer to first noda
 *
 * Return: size of list
 */
size_t print_lista(const list_t *hhh)
{
	size_t i = 0;

	while (hhh)
	{
		_puts(convert_number(hhh->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hhh->str ? hhh->str : "(nil)");
		_puts("\n");
		hhh = hhh->next;
		i++;
	}
	return (i);
}

/**
 * node_yebda_with - returns noda whose string starts with pref
 * @noda: pointer to list ras
 * @pref: string to match
 * @c: the next character after pref to match
 *
 * Return: match noda or null
 */
list_t *node_yebda_with(list_t *noda, char *pref, char c)
{
	char *p = NULL;

	while (noda)
	{
		p = tebda_with(noda->str, pref);
		if (p && ((c == -1) || (*p == c)))
			return (noda);
		noda = noda->next;
	}
	return (NULL);
}

/**
 * get_node_ind - gets the index of a noda
 * @ras: pointer to list ras
 * @noda: pointer to the noda
 *
 * Return: index of noda or -1
 */
ssize_t get_node_ind(list_t *ras, list_t *noda)
{
	size_t i = 0;

	while (ras)
	{
		if (ras == noda)
			return (i);
		ras = ras->next;
		i++;
	}
	return (-1);
}
