#include "shell.h"

/**
 * interactive - return true if the shell is in interactive mode
 * @infos: struct address
 *
 * Return: 1 if it is in interactive mode, 0 if it is not
 */
int interactive(infos_t *infos)
{
	return (isatty(STDIN_FILENO) && infos->readfd <= 2);
}

/**
 * is_delims - check if the character is a delimeter
 * @c: the character to check
 * @delims: the delimeter string
 * Return: 1 if it is true, 0 if it is false
 */
int is_delims(char c, char *delims)
{
	while (*delims)
		if (*delims++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - check for alphabetic character
 *@b: The character to be inputed
 *Return: 1 if b is an alphabet, 0 if it is not
 */

int _isalpha(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atois - converts string to an integer
 *@s: the string that should be converted
 *Return: 0 if there are no numbers in string, converted number otherwise
 */

int _atois(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
	if (s[i] >= '0' && s[i] <= '9')
		{
	flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
