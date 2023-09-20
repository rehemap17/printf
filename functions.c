#include "main.h"


/**
 * print_char - Prints char
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @wid: Width
 * @precision: Precision specification
 * @size: Size specifier
 * 
 * Return: Number of chars printed
 */

int print_char(va_list types, char buffer[],
	int flags, int wid, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, wid, precision, size));
}

/**
 * print_string - Prints string
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @wid: gets width.
 * @precision: Precision specification
 * @size: Size specifier
 * 
 * Return: Number of chars printed
 */

int print_string(va_list types, char buffer[],
	int flags, int wid, int precision, int size)
{
	int length = 0, l;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(wid);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = " ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (wid > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (l = wid - length; l > 0; l--)
				write(1, " ", 1);
			return (wid);
		}
		else
		{
			for (l = wid - length; l > 0; l--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (wid);
		}
	}

	return (write(1, str, length));
}

/**
 * print_percent - Prints percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @wid: gets width.
 * @precision: Precision specification
 * @size: Size specifier
 * 
 * Return: Number of chars printed
 */

int print_percent(va_list types, char buffer[],
	int flags, int wid, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(wid);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - Print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @wid: gets width.
 * @precision: Precision specification
 * @size: Size specifier
 * 
 * Return: Number of chars printed
 */

int print_int(va_list types, char buffer[],
	int flags, int wid, int precision, int size)
{
	int l = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[l--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[l--] = (num % 10) + '0';
		num /= 10;
	}

	l++;

	return (write_number(is_negative, l, buffer, flags, wid, precision, size));
}

/**
 * print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @wid: gets width.
 * @precision: Precision specification
 * @size: Size specifier
 * 
 * Return: Numbers of char printed.
 */

int print_binary(va_list types, char buffer[],
	int flags, int wid, int precision, int size)
{
	unsigned int n, p, l, sum;
	unsigned int b[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(wid);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	p = 2147483648;
	b[0] = n / p;
	for (l = 1; l < 32; l++)
	{
		p /= 2;
		b[l] = (n / p) % 2;
	}
	for (l = 0, sum = 0, count = 0; l < 32; l++)
	{
		sum += b[l];
		if (sum || l == 31)
		{
			char z = '0' + b[l];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

/**
 * print_unsigned - Prints an unsigned number
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @wid: gets width
 * @precision: Precision specification
 * @size: Size specifier
 * 
 * Return: Number of chars printed.
 */

int print_unsigned(va_list types, char buffer[],
	int flags, int wid, int precision, int size)
{
	int l = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[l--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[l--] = (num % 10) + '0';
		num /= 10;
	}

	l++;

	return (write_unsgnd(0, l, buffer, flags, wid, precision, size));
}

/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @wid: gets width
 * @precision: Precision specification
 * @size: Size specifier
 * 
 * Return: Number of chars printed
 */

int print_octal(va_list types, char buffer[],
	int flags, int wid, int precision, int size)
{

	int l = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(wid);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[l--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[l--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[l--] = '0';

	l++;

	return (write_unsgnd(0, l, buffer, flags, wid, precision, size));
}

/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @wid: gets width
 * @precision: Precision specification
 * @size: Size specifier
 * 
 * Return: Number of chars printed
 */

int print_hexadecimal(va_list types, char buffer[],
	int flags, int wid, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', wid, precision, size));
}

/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @wid: gets width
 * @precision: Precision specification
 * @size: Size specifier
 * 
 * Return: Number of chars printed
 */

int print_hexa_upper(va_list types, char buffer[],
	int flags, int wid, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', wid, precision, size));
}

/**
 * print_hexa - Prints hexadecimal number in lower or upper
 * @types: List of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @wid: gets width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * 
 * Return: Number of chars printed
 */

int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int wid, int precision, int size)
{
	int l = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(wid);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[l--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[l--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[l--] = flag_ch;
		buffer[l--] = '0';
	}

	l++;

	return (write_unsgnd(0, l, buffer, flags, wid, precision, size));
}

/**
 * print_pointer - Prints the value of b pointer variable
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @wid: gets width
 * @precision: Precision specification
 * @size: Size specifier
 * 
 * Return: Number of chars printed.
 */

int print_pointer(va_list types, char buffer[],
	int flags, int wid, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1;
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(wid);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	return (write_pointer(buffer, ind, length,
		wid, flags, padd, extra_c, padd_start));
}

/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @wid: gets width
 * @precision: Precision specification
 * @size: Size specifier
 * 
 * Return: Number of chars printed
 */

int print_non_printable(va_list types, char buffer[],
	int flags, int wid, int precision, int size)
{
	int l = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(wid);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[l] != '\0')
	{
		if (is_printable(str[l]))
			buffer[l + offset] = str[l];
		else
			offset += append_hexa_code(str[l], buffer, l + offset);

		l++;
	}

	buffer[l + offset] = '\0';

	return (write(1, buffer, l + offset));
}

/**
 * print_reverse - Prints reverse string.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @wid: gets width
 * @precision: Precision specification
 * @size: Size specifier
 * 
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int wid, int precision, int size)
{
	char *str;
	int l, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(wid);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (l = 0; str[l]; l++)
		;

	for (l = l - 1; l >= 0; l--)
	{
		char z = str[l];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - Prints string in rot13.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @wid: gets width
 * @precision: Precision specification
 * @size: Size specifier
 * 
 * Return: Numbers of chars printed
 */

int print_rot13string(va_list types, char buffer[],
	int flags, int wid, int precision, int size)
{
	char x;
	char *str;
	unsigned int l, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(wid);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (l = 0; str[l]; l++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[l])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[l];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
