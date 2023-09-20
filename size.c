#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @c: List of arguments to be printed.
 *
 * Return: Precision.
 */

int get_size(const char *format, int *c)
{
	int curr_i = *c + 1;
	int size = 0;

	if (format[curr_i] == 'l')
		size = S_LONG;
	else if (format[curr_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*c = curr_i - 1;
	else
		*c = curr_i;

	return (size);
}
