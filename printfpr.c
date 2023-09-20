#include "main.h"

/**
 * _printf - Printf function
 * @format: Format.
 * 
 * Return: Printed chars.
 */

int _printf(const char *format, ...)
{
	int f, printed = 0, chars_printed = 0;
	int flg, wid, p, size, buff_ind = 0;
	va_list arg;
	char buffer[BUFFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(arg, format);

	for (f = 0; format && format[f] != '\0'; f++)
	{
		if (format[f] != '%')
		{
			buffer[buff_ind++] = format[f];
			if (buff_ind == BUFFER_SIZE)
				print_buffer(buffer, &buff_ind);
			chars_printed++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flg = hand_flg(format, &f);
			wid = hand_wi(format, &f, arg);
			p = hand_p(format, &f, arg);
			size = hand_size(format, &f);
			++f;
			printed = handle_print(format, &f, arg, buffer,
				flg, wid, p, size);
			if (printed == -1)
				return (-1);
			chars_printed += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(arg);
	return (chars_printed);
}

/**
 * print_buffer - Prints the contents of the buffer
 * @buffer: Array of chars
 * @buff_ind: Index to add next char, represents the length.
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
