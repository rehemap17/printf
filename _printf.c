#include "main.h"

/**
 * _printf - Printf function
 * @format: format.
 * 
 * Return: Printed chars.
 */

int _printf(const char *format, ...)
{
	int e, printed = 0, printed_chars = 0;
	int flags, wid, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (e = 0; format && format[e] != '\0'; e++)
	{
		if (format[e] != '%')
		{
			buffer[buff_ind++] = format[e];
			if (buff_ind == BUFF_SIZE)
			{
				print_buffer(buffer, &buff_ind);
				write(1, &format[e], 1);
				printed_chars++;
			}
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &e);
			wid = get_width(format, &e, list);
			precision = get_precision(format, &e, list);
			size = get_size(format, &e);
			++e;
			printed = handle_print(format, &e, list, buffer,
				flags, wid, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
