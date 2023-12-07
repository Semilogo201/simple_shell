#include "shell.h"

/**
 * is_cmd - it determines if a file is an executable command
 * @infos: it is the info structure
 * @path: it is the path to the file
 *
 * Return: 1 if it is true, 0 if untrue
 */
int is_cmd(infos_t *infos, char *path)
{
	struct stat st;

	(void)infos;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - it duplicates the characters
 * @pathstr: it is the PATH string
 * @start: it is the starting index
 * @stop: it is the stopping index
 *
 * Return: pointer to the new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - it finds this cmd in the PATH string
 * @infos: it is the info structure
 * @pathstr: it is the PATH string
 * @cmd: it is the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(infos_t *infos, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(infos, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(infos, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

