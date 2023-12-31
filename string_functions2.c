#include "shell.h"

/**
 * _strcpy_ - copies a string
 * @destination: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy_(char *destination, char *src)
{
	int i = 0;

	if (destination == src || src == 0)
		return (destination);
	while (src[i])
	{
		destination[i] = src[i];
		i++;
	}
	destination[i] = 0;
	return (destination);
}

/**
 * _strdup_ - duplicates a string
 * @str: the string to duplicate string
 *
 * Return: pointer to the duplicated string
 */
char *_strdup_(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *_puts_ - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts_(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar_(str[i]);
		i++;
	}
}

/**
 * _putchar_ - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar_(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
