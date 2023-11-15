#include "shell.h"

/**
 *_eputs_ - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _eputs_(char *string)
{
	int i = 0;

	if (!string)
		return;
	while (string[i] != '\0')
	{
		_eputchar_(string[i]);
		i++;
	}
}

/**
 * _eputchar_ - writes the character ch to stderr
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar_(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}

/**
 * _putfd_ - writes the character ch to given ffd
 * @ch: The character to print
 * @ffd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd_(char ch, int ffd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(ffd, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}

/**
 *_putsfd_ - prints an input string
 * @string: the string to be printed
 * @ffd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd_(char *string, int ffd)
{
	int i = 0;

	if (!string)
		return (0);
	while (*string)
	{
		i += _putfd_(*string++, ffd);
	}
	return (i);
}
