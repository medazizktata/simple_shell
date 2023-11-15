#include "shell.h"

/**
 * get_histoire_fichier - gets the history file
 * @information: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_histoire_fichier(info_t *information)
{
	char *buffer, *directory;

	directory = _getenv_(information, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen_(directory) + _strlen_(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy_(buffer, directory);
	_strcat_(buffer, "/");
	_strcat_(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_histoire - creates a file, or appends to an existing file
 * @information: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_histoire(info_t *information)
{
	ssize_t fdd;
	char *filename = get_histoire_fichier(information);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fdd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdd == -1)
		return (-1);
	for (node = information->history; node; node = node->next)
	{
		_putsfd_(node->str, fdd);
		_putfd_('\n', fdd);
	}
	_putfd_(BUF_FLUSH, fdd);
	close(fdd);
	return (1);
}

/**
 * read_histoire - reads history from file
 * @information: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_histoire(info_t *information)
{
	int i, last = 0, lineehseb = 0;
	ssize_t fdd, rdlength, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_histoire_fichier(information);

	if (!filename)
		return (0);

	fdd = open(filename, O_RDONLY);
	free(filename);
	if (fdd == -1)
		return (0);
	if (!fstat(fdd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlength = read(fdd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlength <= 0)
		return (free(buffer), 0);
	close(fdd);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_histoire_list(information, buffer + last, lineehseb++);
			last = i + 1;
		}
	if (last != i)
		build_histoire_list(information, buffer + last, lineehseb++);
	free(buffer);
	information->histcount = lineehseb;
	while (information->histcount-- >= HIST_MAX)
		delete_node_at_ind(&(information->history), 0);
	renumber_histoire(information);
	return (information->histcount);
}

/**
 * build_histoire_list - adds entry to a history linked list
 * @information: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @lineehseb: the history lineehseb, histcount
 *
 * Return: Always 0
 */
int build_histoire_list(info_t *information, char *buffer, int lineehseb)
{
	list_t *node = NULL;

	if (information->history)
		node = information->history;
	add_noda_end(&node, buffer, lineehseb);

	if (!information->history)
		information->history = node;
	return (0);
}

/**
 * renumber_histoire - renumbers the history linked list after changes
 * @information: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_histoire(info_t *information)
{
	list_t *node = information->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (information->histcount = i);
}
