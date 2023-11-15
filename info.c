#include "shell.h"

/**
 * clear_information - initializes info_t struct
 * @information: struct address
 */
void clear_information(info_t *information)
{
	information->arg = NULL;
	information->argv = NULL;
	information->path = NULL;
	information->argc = 0;
}

/**
 * set_information - initializes info_t struct
 * @information: struct address
 * @av: argument vector array
 */
void set_information(info_t *information, char **av)
{
	int i = 0;

	information->fname = av[0];
	if (information->arg)
	{
		information->argv = strtoww(information->arg, " \t");
		if (!information->argv)
		{

			information->argv = malloc(sizeof(char *) * 2);
			if (information->argv)
			{
				information->argv[0] = _strdup_(information->arg);
				information->argv[1] = NULL;
			}
		}
		for (i = 0; information->argv && information->argv[i]; i++)
			;
		information->argc = i;

		replace_alias(information);
		replace_vars(information);
	}
}

/**
 * free_information - frees info_t struct fields
 * @information: struct address
 * @everything: true if freeing everything fields
 */
void free_information(info_t *information, int everything)
{
	fffree(information->argv);
	information->argv = NULL;
	information->path = NULL;
	if (everything)
	{
		if (!information->cmd_buf)
			free(information->arg);
		if (information->env)
			free_lista(&(information->env));
		if (information->history)
			free_lista(&(information->history));
		if (information->alias)
			free_lista(&(information->alias));
		fffree(information->environ);
			information->environ = NULL;
		bfreee((void **)information->cmd_buf);
		if (information->readfd > 2)
			close(information->readfd);
		_putchar_(BUF_FLUSH);
	}
}
