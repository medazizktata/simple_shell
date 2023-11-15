#include "shell.h"

/**
 **_memset_ - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset_(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * fffree - frees a string of stringsss
 * @ppp: string of stringssss
 */
void fffree(char **ppp)
{
	char **a = ppp;

	if (!ppp)
		return;
	while (*ppp)
		free(*ppp++);
	free(a);
}

/**
 * _realloc_ - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @size_9dim: byte size of previous block
 * @size_jdid: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc_(void *ptr, unsigned int size_9dim, unsigned int size_jdid)
{
	char *p;

	if (!ptr)
		return (malloc(size_jdid));
	if (!size_jdid)
		return (free(ptr), NULL);
	if (size_jdid == size_9dim)
		return (ptr);

	p = malloc(size_jdid);
	if (!p)
		return (NULL);

	size_9dim = size_9dim < size_jdid ? size_9dim : size_jdid;
	while (size_9dim--)
		p[size_9dim] = ((char *)ptr)[size_9dim];
	free(ptr);
	return (p);
}
