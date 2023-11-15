#include "shell.h"

/**
 * _myenv_ - prints the current environment
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0 0 0
 */
int _myenv_(info_t *inf)
{
	print_list_string(inf->env);
	return (0);
}

/**
 * _getenv_ - gets the value of an environ variable
 * @inf: Structure containing potential arguments. Used to maintain
 * @nm: env var nm
 *
 * Return: the value the legend
 */
char *_getenv_(info_t *inf, const char *nm)
{
	list_t *nd = inf->env;
	char *k;

	while (nd)
	{
		k = tebda_with(nd->str, nm);
		if (k && *k)
			return (k);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * _mysetenv_ - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv_(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs_("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv_(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv_ - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv_(info_t *inf)
{
	int i;

	if (inf->argc == 1)
	{
		_eputs_("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= inf->argc; i++)
		_unsetenv_(inf, inf->argv[i]);

	return (0);
}

/**
 * populate_env_lista - populates env linked list
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0 always 0 zah
 */
int populate_env_lista(info_t *inf)
{
	list_t *nd = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_noda_end(&nd, environ[i], 0);
	inf->env = nd;
	return (0);
}
