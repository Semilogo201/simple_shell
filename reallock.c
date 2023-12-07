#include "shell.h"

/**
 **_memset - it fills the memory with a constant byte
 *@p: it is the pointer to the memory area
 *@b: it is the byte to fill *s with
 *@n: it is the amount of bytes to fill
 *Return: (s) a pointer to memory area s
 */
char *_memset(char *p, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		p[i] = b;
	return (p);
}

/**
 * ffree - it frees a string of strings
 * @ss: the string of strings
 */
void ffree(char **ss)
{
	char **a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * _realloc - it reallocates a block of memory
 * @ptr: the pointer to the previous malloc'ated block
 * @old_size: the size of byte of the previous block
 * @new_size: the size of byte of the new block
 *
 * Return: the pointer to the old block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *s;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	s = malloc(new_size);
	if (!s)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		s[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (s);
}
