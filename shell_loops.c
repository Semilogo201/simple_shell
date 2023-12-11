#include "shell.h"

/**
 * hsh - the main shell loop
 * @infos: it is the parameter & return info structure
 * @av: it is the argument vector from the main()
 *
 * Return: 0 when it is success, 1 on error, or error code
 */
int hsh(infos_t *infos, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_infos(infos);
		if (interactive(infos))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(infos);
		if (r != -1)
		{
			set_infos(infos, av);
			builtin_ret = find_builtin(infos);
			if (builtin_ret == -1)
				find_cmd(infos);
		}
		else if (interactive(infos))
			_putchar('\n');
		free_infos(infos, 0);
	}
	write_history(infos);
	free_infos(infos, 1);
	if (!interactive(infos) && infos->status)
		exit(infos->status);
	if (builtin_ret == -2)
	{
		if (infos->err_num == -1)
			exit(infos->status);
		exit(infos->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - it finds a built-in command
 * @infos: it is the parameter & return info structure
 *
 * Return: -1 if the built-in is not found,
 *			0 if built-in is executed successfully,
 *			1 if built-in is found but not successful,
 *			-2 if built-in signals exist()
 */
int find_builtin(infos_t *infos)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(infos->argv[0], builtintbl[i].type) == 0)
		{
			infos->line_count++;
			built_in_ret = builtintbl[i].func(infos);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - it finds a command in the PATH
 * @infos: it is the parameter & the return info structure
 *
 * Return: void
 */
void find_cmd(infos_t *infos)
{
	char *path = NULL;
	int i, k;

	infos->path = infos->argv[0];
	if (infos->linecount_flag == 1)
	{
		infos->line_count++;
		infos->linecount_flag = 0;
	}
	for (i = 0, k = 0; infos->arg[i]; i++)
		if (!is_delims(infos->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(infos, _getenv(infos, "PATH="), infos->argv[0]);
	if (path)
	{
		infos->path = path;
		fork_cmd(infos);
	}
	else
	{
		if ((interactive(infos) || _getenv(infos, "PATH=")
			|| infos->argv[0][0] == '/') && is_cmd(infos, infos->argv[0]))
			fork_cmd(infos);
		else if (*(infos->arg) != '\n')
		{
			infos->status = 127;
			print_error(infos, "not found\n");
		}
	}
}

/**
 * fork_cmd - it forks an exec thread to run the cmd
 * @infos: it is the parameter & the return info structure
 *
 * Return: void
 */
void fork_cmd(infos_t *infos)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT THE ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infos->path, infos->argv, get_environ(infos)) == -1)
		{
			free_infos(infos, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT THE ERROR FUNCTION */
	}
	else
	{
		wait(&(infos->status));
		if (WIFEXITED(infos->status))
		{
			infos->status = WEXITSTATUS(infos->status);
			if (infos->status == 126)
				print_error(infos, "Permission denied\n");
		}
	}
}
