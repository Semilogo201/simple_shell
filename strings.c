#include "shell.h"

/**
 * _strlen - it returns the length of a string
 * @sl: it is the string whose length is to be checked
 *
 * Return: the integer length of the string
 */
int _strlen(char *sl)
{
	int i = 0;

	if (!sl)
		return (0);

	while (*sl++)
		i++;
	return (i);
}

/**
 * _strcmp - it performs the lexicographic comparison of two strangs.
 * @sl1: is the first strang
 * @sl2: is the second strang
 *
 * Return:-ve if sl1 < sl2, +ve if sl1 > sl2, zero if sl1 == to sl2
 */
int _strcmp(char *sl1, char *sl2)
{
	while (*sl1 && *sl2)
	{
		if (*sl1 != *sl2)
			return (*sl1 - *sl2);
		sl1++;
		sl2++;
	}
	if (*sl1 == *sl2)
		return (0);
	else
		return (*sl1 < *sl2 ? -1 : 1);
}

/**
 * starts_with - it checks if the needle starts with an haystack
 * @haystack: the string to search
 * @needle: it is the substring to find
 *
 * Return: the address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - it concatenates two strings
 * @dest: it is the destination buffer
 * @src: it is the source buffer
 *
 * Return: the pointer to the destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
