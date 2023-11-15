#include "shell.h"

/**
 * get_environment - returns the string array copy of our environ
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environment(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = lista_to_strings(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv_ - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @variable: the string env variable property
 */
int _unsetenv_(info_t *inf, char *variable)
{
	list_t *noda = inf->env;
	size_t i = 0;
	char *p;

	if (!noda || !variable)
		return (0);

	while (noda)
	{
		p = tebda_with(noda->str, variable);
		if (p && *p == '=')
		{
			inf->env_changed = delete_node_at_ind(&(inf->env), i);
			i = 0;
			noda = inf->env;
			continue;
		}
		noda = noda->next;
		i++;
	}
	return (inf->env_changed);
}

/**
 * _setenv_ - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: the string env variable property
 * @valeur: the string env variable valeur
 *  Return: Always 0
 */
int _setenv_(info_t *inf, char *variable, char *valeur)
{
	char *buffer = NULL;
	list_t *noda;
	char *p;

	if (!variable || !valeur)
		return (0);

	buffer = malloc(_strlen_(variable) + _strlen_(valeur) + 2);
	if (!buffer)
		return (1);
	_strcpy_(buffer, variable);
	_strcat_(buffer, "=");
	_strcat_(buffer, valeur);
	noda = inf->env;
	while (noda)
	{
		p = tebda_with(noda->str, variable);
		if (p && *p == '=')
		{
			free(noda->str);
			noda->str = buffer;
			inf->env_changed = 1;
			return (0);
		}
		noda = noda->next;
	}
	add_noda_end(&(inf->env), buffer, 0);
	free(buffer);
	inf->env_changed = 1;
	return (0);
}
