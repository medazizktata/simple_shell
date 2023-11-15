#include "shell.h"

/**
 * is_command - determines if a file is an executable command
 * @information: the information struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_command(info_t *information, char *path)
{
	struct stat st;

	(void)information;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupp_chars - duplicates characters
 * @pathstring: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dupp_chars(char *pathstring, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstring[i] != ':')
			buffer[k++] = pathstring[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_path_ - finds this cmd in the PATH string
 * @information: the information struct
 * @pathstring: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path_(info_t *information, char *pathstring, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstring)
		return (NULL);
	if ((_strlen_(cmd) > 2) && tebda_with(cmd, "./"))
	{
		if (is_command(information, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstring[i] || pathstring[i] == ':')
		{
			path = dupp_chars(pathstring, curr_pos, i);
			if (!*path)
				_strcat_(path, cmd);
			else
			{
				_strcat_(path, "/");
				_strcat_(path, cmd);
			}
			if (is_command(information, path))
				return (path);
			if (!pathstring[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
