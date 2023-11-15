#include "shell.h"

/**
 * is_chaiin - test if current char in buffer is a chain delimeter
 * @information: the parameter struct
 * @buffer: the char buffer
 * @pos: address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chaiin(info_t *information, char *buffer, size_t *pos)
{
	size_t j = *pos;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		information->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		information->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		information->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = j;
	return (1);
}

/**
 * check_chaiin - checks we should continue chaining based on last status
 * @inf: the parameter struct
 * @buf: the char buffer
 * @pos: address of current position in buffer
 * @i: starting position in buffer
 * @lg: length of buffer
 *
 * Return: Void
 */
void check_chaiin(info_t *inf, char *buf, size_t *pos, size_t i, size_t lg)
{
	size_t j = *pos;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buf[i] = 0;
			j = lg;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buf[i] = 0;
			j = lg;
		}
	}

	*pos = j;
}

/**
 * replace_aliias - replaces an aliases in the tokenized string
 * @information: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_aliias(info_t *information)
{
	int i;
	list_t *nd;
	char *ps;

	for (i = 0; i < 10; i++)
	{
		nd = node_yebda_with(information->alias, information->argv[0], '=');
		if (!nd)
			return (0);
		free(information->argv[0]);
		ps = _strchr_(nd->str, '=');
		if (!p)
			return (0);
		ps = _strdup_(ps + 1);
		if (!p)
			return (0);
		information->argv[0] = ps;
	}
	return (1);
}

/**
 * replace_varss - replaces vars in the tokenized string
 * @information: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_varss(info_t *information)
{
	int i = 0;
	list_t *nd;

	for (i = 0; information->argv[i]; i++)
	{
		if (information->argv[i][0] != '$' || !information->argv[i][1])
			continue;

		if (!_strcmp_(information->argv[i], "$?"))
		{
			replace_str(&(information->argv[i]),
				_strdup_(convert_nombre(information->status, 10, 0)));
			continue;
		}
		if (!_strcmp_(information->argv[i], "$$"))
		{
			replace_str(&(information->argv[i]),
				_strdup_(convert_nombre(getpid(), 10, 0)));
			continue;
		}
		nd = node_yebda_with(information->env, &information->argv[i][1], '=');
		if (nd)
		{
			replace_str(&(information->argv[i]),
				_strdup_(_strchr_(nd->str, '=') + 1));
			continue;
		}
		replace_str(&information->argv[i], _strdup_(""));

	}
	return (0);
}

/**
 * replace_str - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
