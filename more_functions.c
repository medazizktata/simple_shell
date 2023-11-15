#include "shell.h"

/**
 * interactif - returns true if shell is interactif mode
 * @info: struct address
 *
 * Return: 1 if interactif mode, 0 otherwise
 */
int interactif(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim_ - checks if character is a delimeter
 * @ch: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim_(char ch, char *delim)
{
	while (*delim)
		if (*delim++ == ch)
			return (1);
	return (0);
}

/**
 *_isalpha_ - checks for alphabetic character
 *@ch: The character to input
 *Return: 1 if ch is alphabetic, 0 otherwise
 */

int _isalpha_(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi_ - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi_(char *str)
{
	int i, sign = 1, _3alam = 0, outputa;
	unsigned int resultat = 0;

	for (i = 0;  str[i] != '\0' && _3alam != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			_3alam = 1;
			resultat *= 10;
			resultat += (str[i] - '0');
		}
		else if (_3alam == 1)
			_3alam = 2;
	}

	if (sign == -1)
		outputa = -resultat;
	else
		outputa = resultat;

	return (outputa);
}
