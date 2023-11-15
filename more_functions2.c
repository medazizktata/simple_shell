#include "shell.h"

/**
 * _erratoi_ - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi_(char *str)
{
	int i = 0;
	unsigned long int resultat = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			resultat *= 10;
			resultat += (str[i] - '0');
			if (resultat > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (resultat);
}

/**
 * print_8alta - prints an error message
 * @information: the parameter & return information struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_8alta(info_t *information, char *estr)
{
	_eputs_(information->fname);
	_eputs_(": ");
	print_ddd(information->line_count, STDERR_FILENO);
	_eputs_(": ");
	_eputs_(information->argv[0]);
	_eputs_(": ");
	_eputs_(estr);
}

/**
 * print_ddd - function prints a decimal (integer) number (base 10)
 * @inputa: the inputa
 * @fddd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_ddd(int inputa, int fddd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fddd == STDERR_FILENO)
		__putchar = _eputchar;
	if (inputa < 0)
	{
		_abs_ = -inputa;
		__putchar('-');
		count++;
	}
	else
		_abs_ = inputa;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_nombre - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @a3lem: argument a3lem
 *
 * Return: string
 */
char *convert_nombre(long int num, int base, int a3lem)
{
	static char *arrrray;
	static char buffer[50];
	char sign = 0;
	char *pointer;
	unsigned long n = num;

	if (!(a3lem & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	arrrray = a3lem & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';

	do	{
		*--pointer = arrrray[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--pointer = sign;
	return (pointer);
}

/**
 * remove_cmnts - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_cmnts(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}
