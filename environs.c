#include "shell.h"

/**
 * _myenv - it prints the current environment
 * @infos: Structure that contains potential arguments. Used in maintaining
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(infos_t *infos)
{
	print_list_str(infos->env);
	return (0);
}

/**
 * _getenv - it gets the value of an environ variable
 * @infos: Structure that contains potential arguments. Used in maintaining
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(infos_t *infos, const char *name)
{
	list_t *node = infos->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - it will initialize a new environment variable,
 *             or modify an already existing one
 * @infos: Structure that contains potential arguments. Used in maintaining
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(infos_t *infos)
{
	if (infos->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(infos, infos->argv[1], infos->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove any environment variable
 * @infos: Structure that contains potential arguments. Used in maintaining
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(infos_t *infos)
{
	int i;

	if (infos->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= infos->argc; i++)
		_unsetenv(infos, infos->argv[i]);

	return (0);
}

/**
 * populate_env_list - it populates the env linked list
 * @infos: Structure that contains potential arguments. Used in maintaining
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(infos_t *infos)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	infos->env = node;
	return (0);
}

