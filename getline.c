#include "shell.h"

/**
 * input_buffer - buffers chained commands
 * @information: parameter struct
 * @buffer: address of buffer
 * @length: address of length var
 *
 * Return: bytes read
 */
ssize_t input_buffer(info_t *information, char **buffer, size_t *length)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)information->cmd_buf);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigint3Handler);
#if USE_GETLINE
		r = getline(buffer, &len_p, stdin);
#else
		r = _getline_(information, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			information->linecount_flag = 1;
			remove_cmnts(*buffer);
			build_histoire_list(information, *buffer, information->histcount++);
			/* if (_strchr_(*buffer, ';')) is this a command chain? */
			{
				*length = r;
				information->cmd_buf = buffer;
			}
		}
	}
	return (r);
}

/**
 * get_3input - gets a line minus the newline
 * @information: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_3input(info_t *information)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t i, j, length;
	ssize_t r = 0;
	char **buf_p = &(information->arg), *p;

	_putchar_(BUF_FLUSH);
	r = input_buffer(information, &buffer, &length);
	if (r == -1) /* EOF */
		return (-1);
	if (length)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buffer position */
		p = buffer + i; /* get pointer for return */

		check_chaiin(information, buffer, &j, i, length);
		while (j < length) /* iterate to semicolon or end */
		{
			if (is_chaiin(information, buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= length) /* reached end of buffer? */
		{
			i = length = 0; /* reset position and length */
			information->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen_(p)); /* return length of current command */
	}

	*buf_p = buffer; /* else not a chain, pass back buffer from _getline_() */
	return (r); /* return length of buffer from _getline_() */
}

/**
 * read_buffer - reads a buffer
 * @information: parameter struct
 * @buffer: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buffer(info_t *information, char *buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(information->readfd, buffer, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline_ - gets the next line of input from STDIN
 * @information: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline_(info_t *information, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, length;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == length)
		i = length = 0;

	r = read_buffer(information, buffer, &length);
	if (r == -1 || (r == 0 && length == 0))
		return (-1);

	c = _strchr_(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : length;
	new_p = _realloc_(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat_(new_p, buffer + i, k - i);
	else
		_strncpy_(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigint3Handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigint3Handler(__attribute__((unused))int sig_num)
{
	_puts_("\n");
	_puts_("$ ");
	_putchar_(BUF_FLUSH);
}
