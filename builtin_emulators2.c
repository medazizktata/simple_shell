#include "shell.h"

/**
 * _myhistory_ - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory_(info_t *information)
{
	print_lista(information->history);
	return (0);
}

/**
 * unset_aliaas - sets alias to string
 * @inf: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_aliaas(info_t *inf, char *string)
{
	char *p, c;
	int ret;

	p = _strchr_(string, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_ind(&(inf->alias),
		get_node_ind(inf->alias, node_yebda_with(inf->alias, string, -1)));
	*p = c;
	return (ret);
}

/**
 * set_aliaas - sets alias to string
 * @information: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_aliaas(info_t *information, char *string)
{
	char *p;

	p = _strchr_(string, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_aliaas(information, string));

	unset_aliaas(information, string);
	return (add_noda_end(&(information->alias), string, 0) == NULL);
}

/**
 * print_aliaas - prints an alias string
 * @nd: the alias nd
 *
 * Return: Always 0 on success, 1 on error
 */
int print_aliaas(list_t *nd)
{
	char *p = NULL, *a = NULL;

	if (nd)
	{
		p = _strchr_(nd->string, '=');
		for (a = nd->string; a <= p; a++)
			_putchar_(*a);
		_putchar_('\'');
		_puts_(p + 1);
		_puts_("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myaliaas_ - mimics the alias builtin (man alias)
 * @inff: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myaliaas_(info_t *inff)
{
	int i = 0;
	char *p = NULL;
	list_t *nd = NULL;

	if (inff->argc == 1)
	{
		nd = inff->alias;
		while (nd)
		{
			print_aliaas(nd);
			nd = nd->next;
		}
		return (0);
	}
	for (i = 1; inff->argv[i]; i++)
	{
		p = _strchr_(inff->argv[i], '=');
		if (p)
			set_aliaas(inff, inff->argv[i]);
		else
			print_aliaas(node_yebda_with(inff->alias, inff->argv[i], '='));
	}

	return (0);
}
