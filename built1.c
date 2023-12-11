#include "shell.h"

/**
 * _myhistory - it displays the history list, one command by a line, preceded
 *              with line numbers, starting it at 0.
 * @infos: Structure that contains potential arguments. Used in maintaining
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(infos_t *infos)
{
	print_lists(infos->history);
	return (0);
}

/**
 * unset_alias - it sets alias to a string
 * @infos: parameter structure
 * @str: the string alias
 *
 * Return: Always 0 when it is success, 1 when it is error
 */
int unset_alias(infos_t *infos, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(infos->alias),
		get_node_index(infos->alias, node_start_with(infos->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - it sets alias to string
 * @infos: parameter structure
 * @str: the string alias
 *
 * Return: Always 0 when it is success, 1 when it is error
 */
int set_alias(infos_t *infos, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(infos, str));

	unset_alias(infos, str);
	return (add_node_end(&(infos->alias), str, 0) == NULL);
}

/**
 * print_alias - it prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 when it is success, 1 when it is error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - it mimics the alias builtin (man alias)
 * @infos: Structure that contains potential arguments. Used in maintaining
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(infos_t *infos)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (infos->argc == 1)
	{
		node = infos->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; infos->argv[i]; i++)
	{
		p = _strchr(infos->argv[i], '=');
		if (p)
			set_alias(infos, infos->argv[i]);
		else
			print_alias(node_start_with(infos->alias, infos->argv[i], '='));
	}

	return (0);
}
