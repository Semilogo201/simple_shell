#include "shell.h"

/**
 * _myexit - exits out of the shell
 * @infos: Structure that contains potential arguments. Used in maintaining
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if infos.argv[0] != "exit"
 */
int _myexit(infos_t *infos)
{
	int exitcheck;

	if (infos->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratois(infos->argv[1]);
		if (exitcheck == -1)
		{
			infos->status = 2;
			print_error(infos, "Illegal number: ");
			_eputs(infos->argv[1]);
			_eputchar('\n');
			return (1);
		}
		infos->err_num = _erratois(infos->argv[1]);
		return (-2);
	}
	infos->err_num = -1;
	return (-2);
}

/**
 * _mycd - it changes the current directory of the process
 * @infos: Structure that contains potential arguments. Used in maintaining
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(infos_t *infos)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!infos->argv[1])
	{
		dir = _getenv(infos, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(infos, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(infos->argv[1], "-") == 0)
	{
		if (!_getenv(infos, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(infos, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(infos, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(infos->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(infos, "can't cd to ");
		_eputs(infos->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(infos, "OLDPWD", _getenv(infos, "PWD="));
		_setenv(infos, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - it changes the current directory of the process
 * @infos: Structure that contains potential arguments. Used in maintaining
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(infos_t *infos)
{
	char **arg_array;

	arg_array = infos->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
