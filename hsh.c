#include "shell.h"

/**
 * hshsh - main shell loop
 * @information: the parameter & return information struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hshsh(info_t *information, char **av)
{
	ssize_t r = 0;
	int builting_ret = 0;

	while (r != -1 && builting_ret != -2)
	{
		clear_information(information);
		if (interactif(information))
			_puts_("$ ");
		_eputchar_(BUF_FLUSH);
		r = get_3input(information);
		if (r != -1)
		{
			set_information(information, av);
			builting_ret = find_builting(information);
			if (builting_ret == -1)
				find_command(information);
		}
		else if (interactif(information))
			_putchar_('\n');
		free_information(information, 0);
	}
	write_histoire(information);
	free_information(information, 1);
	if (!interactif(information) && information->status)
		exit(information->status);
	if (builting_ret == -2)
	{
		if (information->err_num == -1)
			exit(information->status);
		exit(information->err_num);
	}
	return (builting_ret);
}

/**
 * find_builting - finds a builtin command
 * @information: the parameter & return information struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builting(info_t *information)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp_(information->argv[0], builtintbl[i].type) == 0)
		{
			information->line_count++;
			built_in_ret = builtintbl[i].func(information);
			break;
		}
	return (built_in_ret);
}

/**
 * find_command - finds a command in PATH
 * @inf: the parameter & return information struct
 *
 * Return: void
 */
void find_command(info_t *inf)
{
	char *path = NULL;
	int i, k;

	inf->path = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (i = 0, k = 0; inf->arg[i]; i++)
		if (!is_delim_(inf->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path_(inf, _getenv_(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_command(inf);
	}
	else
	{
		if ((interactif(inf) || _getenv_(inf, "PATH=")
			|| inf->argv[0][0] == '/') && is_command(inf, inf->argv[0]))
			fork_command(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_8alta(inf, "not found\n");
		}
	}
}

/**
 * fork_command - forks a an exec thread to run cmd
 * @info: the parameter & return information struct
 *
 * Return: void
 */
void fork_command(info_t *info)
{
	pid_t child_processid;

	child_processid = fork();
	if (child_processid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_processid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_8alta(info, "Permission denied\n");
		}
	}
}
