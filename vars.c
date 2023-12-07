#include "shell.h"

/**
 * is_chain - it tests if current character in buffer is chain delimeter
 * @infos: parameter structure
 * @buf: char buffer
 * @r: the address of current position in buffer
 *
 * Return: 1 if it is a chain delimeter, 0 if it is not
 */
int is_chain(infos_t *infos, char *buf, size_t *r)
{
	size_t j = *r;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		infos->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		infos->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found the end of this command */
	{
		buf[j] = 0; /* replace the semicolon with null */
		infos->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*r = j;
	return (1);
}

/**
 * check_chain - checks continue chaining based on the last status
 * @infos: parameter structure
 * @buf: char buffer
 * @r: the address of current position in buf
 * @i: the starting position in buf
 * @len: the length of buf
 *
 * Return: Void
 */
void check_chain(infos_t *infos, char *buf, size_t *r, size_t i, size_t len)
{
	size_t j = *r;

	if (infos->cmd_buf_type == CMD_AND)
	{
		if (infos->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (infos->cmd_buf_type == CMD_OR)
	{
		if (!infos->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*r = j;
}

/**
 * replace_alias - it replaces an alias in the tokenized string
 * @infos: parameter structure
 *
 * Return: 1 if it is replaced, 0 if it is not
 */
int replace_alias(infos_t *infos)
{
	int i;
	list_t *node;
	char *r;

	for (i = 0; i < 10; i++)
	{
		node = node_start_with(infos->alias, infos->argv[0], '=');
		if (!node)
			return (0);
		free(infos->argv[0]);
		r = _strchr(node->str, '=');
		if (!r)
			return (0);
		r = _strdup(r + 1);
		if (!r)
			return (0);
		infos->argv[0] = r;
	}
	return (1);
}

/**
 * replace_vars - it replaces vars in the tokenized string
 * @infos: parameter structure
 *
 * Return: 1 if it is replaced, 0 if it is not
 */
int replace_vars(infos_t *infos)
{
	int i = 0;
	list_t *node;

	for (i = 0; infos->argv[i]; i++)
	{
		if (infos->argv[i][0] != '$' || !infos->argv[i][1])
			continue;

		if (!_strcmp(infos->argv[i], "$?"))
		{
			replace_string(&(infos->argv[i]),
				_strdup(convert_number(infos->status, 10, 0)));
			continue;
		}
		if (!_strcmp(infos->argv[i], "$$"))
		{
			replace_string(&(infos->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_start_with(infos->env, &infos->argv[i][1], '=');
		if (node)
		{
			replace_string(&(infos->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&infos->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - it replaces string
 * @old: the address of old string
 * @new: the address of new string
 *
 * Return: 1 if it is replaced, 0 if it is not
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
