#include "shell.h"

/**
 * cfree - it frees a pointer and it NULLs the address
 * @ptrs: the address of the pointer to be freed
 *
 * Return: 1 if it is eventually freed, 0 if not.
 */
int cfree(void **ptrs)
{
	if (ptrs && *ptrs)
	{
		free(*ptrs);
		*ptrs = NULL;
		return (1);
	}
	return (0);
}
