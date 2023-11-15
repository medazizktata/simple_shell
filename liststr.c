#include "shell.hhh"

/**
 * add_noda - adds a noda to the start of the list
 * @ras: address of pointer to ras noda
 * @str: str field of noda
 * @num: noda ind used by history
 *
 * Return: size of list
 */
list_t *add_noda(list_t **ras, const char *str, int num)
{
	list_t *new_ras;

	if (!ras)
		return (NULL);
	new_ras = malloc(sizeof(list_t));
	if (!new_ras)
		return (NULL);
	_memset_((void *)new_ras, 0, sizeof(list_t));
	new_ras->num = num;
	if (str)
	{
		new_ras->str = _strdup_(str);
		if (!new_ras->str)
		{
			free(new_ras);
			return (NULL);
		}
	}
	new_ras->next = *ras;
	*ras = new_ras;
	return (new_ras);
}

/**
 * add_noda_end - adds a noda to the end of the list
 * @ras: address of pointer to ras noda
 * @str: str field of noda
 * @num: noda ind used by history
 *
 * Return: size of list
 */
list_t *add_noda_end(list_t **ras, const char *str, int num)
{
	list_t *new_noda, *noda;

	if (!ras)
		return (NULL);

	noda = *ras;
	new_noda = malloc(sizeof(list_t));
	if (!new_noda)
		return (NULL);
	_memset_((void *)new_noda, 0, sizeof(list_t));
	new_noda->num = num;
	if (str)
	{
		new_noda->str = _strdup_(str);
		if (!new_noda->str)
		{
			free(new_noda);
			return (NULL);
		}
	}
	if (noda)
	{
		while (noda->next)
			noda = noda->next;
		noda->next = new_noda;
	}
	else
		*ras = new_noda;
	return (new_noda);
}

/**
 * print_list_string - prints only the str element of a list_t linked list
 * @hhh: pointer to first noda
 *
 * Return: size of list
 */
size_t print_list_string(const list_t *hhh)
{
	size_t i = 0;

	while (hhh)
	{
		_puts_(hhh->str ? hhh->str : "(nil)");
		_puts_("\n");
		hhh = hhh->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_ind - deletes noda at given ind
 * @ras: address of pointer to first noda
 * @ind: ind of noda to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_ind(list_t **ras, unsigned int ind)
{
	list_t *noda, *prev_node;
	unsigned int i = 0;

	if (!ras || !*ras)
		return (0);

	if (!ind)
	{
		noda = *ras;
		*ras = (*ras)->next;
		free(noda->str);
		free(noda);
		return (1);
	}
	noda = *ras;
	while (noda)
	{
		if (i == ind)
		{
			prev_node->next = noda->next;
			free(noda->str);
			free(noda);
			return (1);
		}
		i++;
		prev_node = noda;
		noda = noda->next;
	}
	return (0);
}

/**
 * free_lista - frees all nodes of a list
 * @ras_ptr: address of pointer to ras noda
 *
 * Return: void
 */
void free_lista(list_t **ras_ptr)
{
	list_t *noda, *next_node, *ras;

	if (!ras_ptr || !*ras_ptr)
		return;
	ras = *ras_ptr;
	noda = ras;
	while (noda)
	{
		next_node = noda->next;
		free(noda->str);
		free(noda);
		noda = next_node;
	}
	*ras_ptr = NULL;
}
