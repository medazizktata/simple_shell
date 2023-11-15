#include "shell.h"
/**
 * _myexit_ - exits the shell
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if information.argv[0] != "exit"
 */
int _myexit_(info_t *information)
{
	int exitchecker;

	if (information->argv[1])  /* If there is an exit arguement */
	{
		exitchecker = _erratoi_(information->argv[1]);
		if (exitchecker == -1)
		{
			information->status = 2;
			print_8alta(information, "Illegal number: ");
			_eputs_(information->argv[1]);
			_eputchar_('\n');
			return (1);
		}
		information->err_num = _erratoi_(information->argv[1]);
		return (-2);
	}
	information->err_num = -1;
	return (-2);
}

/**
 * _mycd_ - changes the current directory of the process
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd_(info_t *information)
{
	char *s, *directory, buffer[1024];
	int chdirectory_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts_("TODO: >>getcwd failure emsg here<<\n");
	if (!information->argv[1])
	{
		directory = _getenv_(information, "HOME=");
		if (!directory)
			chdirectory_ret = /* TODO: what should this be? */
				chdir((directory = _getenv_(information, "PWD=")) ? directory : "/");
		else
			chdirectory_ret = chdir(directory);
	}
	else if (_strcmp_(information->argv[1], "-") == 0)
	{
		if (!_getenv_(information, "OLDPWD="))
		{
			_puts_(s);
			_putchar_('\n');
			return (1);
		}
		_puts_(_getenv_(information, "OLDPWD=")), _putchar_('\n');
		chdirectory_ret = /* TODO: what should this be? */
			chdir((directory = _getenv_(information, "OLDPWD=")) ? directory : "/");
	}
	else
		chdirectory_ret = chdir(information->argv[1]);
	if (chdirectory_ret == -1)
	{
		print_8alta(information, "can't cd to ");
		_eputs_(information->argv[1]), _eputchar_('\n');
	}
	else
	{
		_setenv_(information, "OLDPWD", _getenv_(information, "PWD="));
		_setenv_(information, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp_ - changes the current directory of the process
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp_(info_t *information)
{
	char **arg_arr;

	arg_arr = information->argv;
	_puts_("help call works. Function not yet implemented \n");
	if (0)
		_puts_(*arg_arr); /* temp att_unused workaround */
	return (0);
}
