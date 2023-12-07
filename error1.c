#include "shell.h"

/**
 * _erratois - it will convert a string to an integer
 * @s: it is the string to be converted
 * Return: 0 if there are no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratois(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: Why does this make the main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - it prints an error message
 * @infos: it is the parameter & return info structure
 * @estr: it the string the contains specified error type
 * Return: 0 if there are no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(infos_t *infos, char *estr)
{
	_eputs(infos->fname);
	_eputs(": ");
	print_d(infos->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(infos->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - the function prints a decimal (integer) number (base 10)
 * @input: it is the input
 * @fd: it is the file descriptor to be written to
 *
 * Return: the number of characters to be printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
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
 * convert_number - it is a converter function, a; clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: a string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments -a function that replaces first instance of '#' with '\0'
 * @buf: the address of the string to modify
 *
 * Return: Always as 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}


